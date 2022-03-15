// Jeremy Renati 2022
// Components of an electronic circuit supporting
// volatages, resistors, currents, inductors, capacitors

#include <sstream>
#include <iomanip>

#ifndef Components_h
#define Components_h

// type, high node, low node, value
class Component {
public:
  Component(char type, std::string p_node, std::string n_node, double value) :
      type_(type), positive_node_(p_node), negative_node_(n_node), value_(value) {}
  ~Component() {}

  std::string string() const;
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

std::string Component::string() const {
  std::ostringstream oss;
  oss << '|' << std::setw(6) << type_ << '|' << std::setw(7)
      << positive_node_ << '|' << std::setw(7) << negative_node_
      << '|' << std::setw(7) << value_ << '|';
  return oss.str();
}

#endif // !Components_h
