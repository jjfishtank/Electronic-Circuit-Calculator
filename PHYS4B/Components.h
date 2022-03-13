// Jeremy Renati
// Components of an electronic circuit including
// Battery, Resistor, 

#include <sstream>

#ifndef Components_h
#define Components_h

class Component {
public:
  Component(char type, std::string p_node, std::string n_node, double value)
    : type_(type), positive_node_(p_node), negative_node_(n_node), value_(value) {}
  ~Component() {}

  std::string toString();

  char type() const { return type_; }
  std::string p_node() const { return positive_node_; }
  std::string n_node() const { return negative_node_; }
  double value() const { return value_; }

private:
  char type_;
  std::string positive_node_;
  std::string negative_node_;
  double value_;
};

std::string Component::toString() {
  std::ostringstream oss;
  oss << type_ << ' ' << positive_node_ << ' ' << negative_node_ << ' ' << value_;
  return oss.str();
}

#endif // !Components_h
