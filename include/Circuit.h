// Jeremy Renati 2022
// Electronic Circuit solver from parsed text file using
// Modified Nodal Analysis (MNA) based on Kirchhoff's voltage and current laws
// Circuit.h

#include "Components.h"
#include <eigen-3.4.0/Eigen/Dense>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

#ifndef Circuit_h
#define Circuit_h

class Circuit {
public:
  Circuit(std::ifstream& fin);
  ~Circuit() {}

  Eigen::MatrixXd SolveCircuit() const;
  std::string string() const;
  friend std::ostream& operator<< (std::ostream&, const Circuit&);

  size_t component_count() const { return components_.size(); }
  size_t voltage_count() const { return voltage_count_; }
  size_t current_count() const { return current_count_; }
  size_t resistor_count() const { return resistor_count_; }
  size_t conductor_count() const { return conductor_count_; }
  size_t inductor_count() const { return inductor_count_; }
  size_t nodes_count() const { return nodes_.size(); }
  Eigen::MatrixXd A_matrix() const { return A_; }
  Eigen::MatrixXd b_matrix() const { return b_; }

  const std::unordered_map<std::string, int>& nodes() const { return nodes_; }

private:
  void CalculateMatrices();

  std::vector<Component> components_;
  std::unordered_map<std::string, int> nodes_;
  size_t voltage_count_, current_count_, resistor_count_,
         conductor_count_, inductor_count_;
  // matrices for MNA
  Eigen::MatrixXd A_, b_;

};

// Parses circuit file and creates component vector.
// Maps node names to ints and calculates MNA matrices.
Circuit::Circuit(std::ifstream& fin) :
    voltage_count_(0), current_count_(0), resistor_count_(0),
    conductor_count_(0), inductor_count_(0) {

  char type = 0;
  std::string p_node, n_node;
  double value = 0.0;
  std::string buffer;
  std::istringstream istream;

  // parse file to create components vector
  if (fin) {
    while (std::getline(fin, buffer, ' ')) {
      type = buffer.front();
      std::getline(fin, buffer, ' ');
      istream.clear();
      istream.str(buffer);
      istream >> p_node;

      std::getline(fin, buffer, ' ');
      istream.clear();
      istream.str(buffer);
      istream >> n_node;

      std::getline(fin, buffer, '\n');
      istream.clear();
      istream.str(buffer);
      istream >> value;

      switch (type) {
        case 'C':
          conductor_count_++;
          break;
        case 'I':
          current_count_++;
          break;
        case 'L':
          inductor_count_++;
          break;
        case 'R':
          resistor_count_++;
          break;
        case 'V':
          voltage_count_++;
          break;
        default:
          break;
      }

      components_.push_back(Component(type, p_node, n_node, value));
    }
  }
  fin.close();

  // default node 0
  nodes_.insert({ "0", 0 });
  // map node names to integers
  for (auto& i : components_) {
    nodes_.insert({ i.p_node() , nodes_.size() });
    nodes_.insert({ i.n_node() , nodes_.size() });
  }

  // Calculate A, b matrices for MNA linear system
  CalculateMatrices();
}

// A matrix { G B }
//          { C D }
// b matrix { v } v = independent voltage sources
//          { j } j = independent current sources
void Circuit::CalculateMatrices() {
  std::ptrdiff_t g2_count = 0, g2_index = 0, matrix_size = 0;

  // g2 refers to components with voltage values
  g2_count = voltage_count_ + inductor_count_; // voltage sources
  matrix_size = nodes_.size() + g2_count - 1;
  g2_index = matrix_size - g2_count;

  A_.resize(matrix_size, matrix_size);
  A_.fill(0.0);
  b_.resize(matrix_size, 1);
  b_.fill(0.0);

  for (auto& i : components_) {
    std::ptrdiff_t p_node = 0, n_node = 0;

    // retrieve mapped node ints
    auto search = nodes_.find(i.p_node());
    p_node = search->second;
    search = nodes_.find(i.n_node());
    n_node = search->second;

    double value = i.value();

    // Modify matrix values for all components with respect to type
    switch (i.type()) {
      case 'C':
        // Capacitor acts as open circuit in static calculation
        break;
      case 'I':
        // signed currents in b matrix, positive entering node, negative leaving node.
        if (p_node != 0)
          b_(p_node - 1) = b_(p_node - 1) - value;
        if (n_node != 0)
          b_(n_node - 1) = b_(n_node - 1) + value;
        break;
      case 'L':
        // Inductor counts as wire in static calculation
        if (p_node != 0) {
          A_(p_node - 1, g2_index)++;
          A_(g2_index, p_node - 1)++;
        }
        if (n_node != 0) {
          A_(n_node - 1, g2_index)--;
          A_(g2_index, n_node - 1)--;
        }

        // 0 voltage
        b_(g2_index) = 0.0;
        g2_index++;
        break;
      case 'R':
        // G-Matrix A
        if (p_node != 0)
          A_(p_node - 1, p_node - 1) = A_(p_node - 1, p_node - 1) + 1.0 / value;
        if (n_node != 0)
          A_(n_node - 1, n_node - 1) = A_(n_node - 1, n_node - 1) + 1.0 / value;
        // Mutual conductance
        if (p_node != 0 && n_node != 0) {
          A_(p_node - 1, n_node - 1) = A_(p_node - 1, n_node - 1) - 1.0 / value;
          A_(n_node - 1, p_node - 1) = A_(n_node - 1, p_node - 1) - 1.0 / value;
        }
        break;
      case 'V':
        if (p_node != 0) {
          A_(p_node - 1, g2_index)++;
          A_(g2_index, p_node - 1)++;
        }
        if (n_node != 0) {
          A_(n_node - 1, g2_index)--;
          A_(g2_index, n_node - 1)--;
        }

        b_(g2_index) = value;
        g2_index++;
        break;
      default:
        break;
    }
  }
}

// Linear system Ax = b
// x = { v } unknown voltages of each node
//     {...} unknown voltages of each node
//     { i } unknown current through all V and L
Eigen::MatrixXd Circuit::SolveCircuit() const {
  Eigen::MatrixXd x = A_.colPivHouseholderQr().solve(b_);
  return x;
}

std::string Circuit::string() const {
  std::ostringstream result;
  result << "| Type | +node | -node | value |\n";
  for (size_t i = 0; i < components_.size(); i++) {
    result << components_[i].string() + '\n';
  }
  return result.str();
}

std::ostream& operator<< (std::ostream& os, const Circuit& c) {
  os << c.string();
  return os;
}

#endif // !Circuit_h
