// Jeremy Renati
// Components of an electronic circuit including
// Battery, Resistor, 

#include <sstream>

#ifndef Components_h
#define Components_h

class Component {
public:
  Component(char type, int p_node, int n_node, double value)
    : type_(type), positive_node_(p_node), negative_node_(n_node), value_(value) {}
  ~Component() {}

  std::string toString();
private:
  char type_;
  int positive_node_;
  int negative_node_;
  double value_;
};

std::string Component::toString() {
  std::ostringstream oss;
  oss << type_ << ' ' << positive_node_ << ' ' << negative_node_ << ' ' << value_;
  return oss.str();
}

#endif // !Components_h
