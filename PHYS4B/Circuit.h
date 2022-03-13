// Jeremy Renati
// Electronic Circuit Simulation

#include "Components.h"
#include <eigen-3.4.0/Eigen/Dense>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#ifndef Circuit_h
#define Circuit_h

class Circuit {
public:
  Circuit(std::ifstream& fin);
  ~Circuit() {}

  //Eigen::MatrixXd SolveCircuit();
  std::string toString();

  size_t component_count() const { return components_.size(); }
  size_t voltage_count() const { return voltage_count_; }
  size_t current_count() const { return current_count_; }
  size_t resistor_count() const { return resistor_count_; }
  size_t nodes_count() const { return nodes_.size(); }
  Eigen::MatrixXd A_matrix() const { return A_; }
  Eigen::MatrixXd b_matrix() const { return b_; }

  const std::unordered_map<std::string, size_t>& nodes() const { return nodes_; }

private:

  void CalculateMatrices();

  std::vector<Component> components_;
  std::unordered_map<std::string, size_t> nodes_;
  size_t voltage_count_, current_count_, resistor_count_, conductor_count_, inductor_count_;
  size_t matrix_size_;
  Eigen::MatrixXd A_, b_;

};

// Parses circuit file and creates component vector
Circuit::Circuit(std::ifstream& fin)
  : voltage_count_(0), current_count_(0), resistor_count_(0)
  , conductor_count_(0), inductor_count_(0), matrix_size_(0) {

  char type = 0;
  size_t count = 0;
  std::string p_node, n_node;
  double value = 0.0;
  std::string buffer;
  std::istringstream istream;

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

  // Populate A, b matrices for MNA linear system
  CalculateMatrices();
}

void Circuit::CalculateMatrices() {
  size_t g2_count = 0, g2_index = 0;
  g2_count = voltage_count_ + inductor_count_;
  matrix_size_ = nodes_.size() + g2_count - 1;
  g2_index = matrix_size_ - g2_count;

  A_.resize(matrix_size_, matrix_size_);
  A_.fill(0.0);
  b_.resize(1, matrix_size_);
  b_.fill(0.0);

  for (auto& i : components_) {
    auto search = nodes_.find(i.p_node());
    size_t p_node = search->second;
    search = nodes_.find(i.n_node());
    size_t n_node = search->second;
    double value = i.value();

    switch (i.type()) {
      case 'C':
        break;
      case 'I':
        // signed currents in b matrix
        if (p_node != 0)
          b_(p_node - 1) = b_(p_node - 1) - value;
        if (n_node != 0)
          b_(n_node - 1) = b_(n_node - 1) + value;
        break;
      case 'L':
        if (p_node != 0) {
          A_(p_node - 1, g2_index)++;
          A_(g2_index, p_node - 1)++;
        }
        if (n_node != 0) {
          A_(n_node - 1, g2_index)--;
          A_(g2_index, n_node - 1)--;
        }

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

/*Eigen::MatrixXd Circuit::SolveCircuit() {

}*/

std::string Circuit::toString() {
  std::string result;
  for (size_t i = 0; i < components_.size(); i++) {
    result = result + components_[i].toString() + '\n';
  }
  return result;
}

#endif // !Circuit_h
