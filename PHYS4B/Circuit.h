// Jeremy Renati
// Electronic Circuit Simulation

#include "Components.h"
#include <list>
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
private:
  std::vector<Component> components_;
  int voltage_count_;
  int current_count_;
  int resistor_count_;
};

// Creates circuit component vector from parsed file
Circuit::Circuit(std::ifstream& fin) : voltage_count_(0), current_count_(0), resistor_count_(0) {
  char type = 0;
  int p_node = 0 , n_node = 0;
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
}

std::string Circuit::toString() {
  std::string result;
  for (int i = 0; i < components_.size(); i++) {
    result = result + components_[i].toString() + '\n';
  }
  return result;
}

#endif // !Circuit_h
