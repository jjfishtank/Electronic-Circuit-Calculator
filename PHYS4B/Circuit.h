// Jeremy Renati
// Electronic Circuit Simulation

#include "Components.h"
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

  std::string toString();

  size_t component_count() const { return components_.size(); }
  size_t voltage_count() const { return voltage_count_; }
  size_t current_count() const { return current_count_; }
  size_t resistor_count() const { return resistor_count_; }
  size_t nodes_count() const { return nodes_.size(); }
  const std::unordered_map<std::string, size_t>& nodes() const { return nodes_; }

private:
  std::vector<Component> components_;
  std::unordered_map<std::string, size_t> nodes_;
  size_t voltage_count_;
  size_t current_count_;
  size_t resistor_count_;
};

// Parses circuit file and creates component vector
Circuit::Circuit(std::ifstream& fin) : voltage_count_(0), current_count_(0), resistor_count_(0) {
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
        case 'V':
          voltage_count_++;
          break;
        case 'R':
          resistor_count_++;
          break;
        case 'I':
          current_count_++;
          break;
        default:
          break;
      }

      components_.push_back(Component(type, p_node, n_node, value));
    }
  }
  fin.close();

  nodes_.insert({ "0", 0 });

  for (auto& i : components_) {
    nodes_.insert({ i.p_node() , nodes_.size() });
    nodes_.insert({ i.p_node() , nodes_.size() });
  }
}

std::string Circuit::toString() {
  std::string result;
  for (size_t i = 0; i < components_.size(); i++) {
    result = result + components_[i].toString() + '\n';
  }
  return result;
}

#endif // !Circuit_h
