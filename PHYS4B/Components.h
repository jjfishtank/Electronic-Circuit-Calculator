// Jeremy Renati
// Components of an electronic circuit including
// Battery, Resistor, 

#ifndef Components_h
#define Components_h

class Component {

};

class Battery : public Component {
public:
  Battery() : _emf(0.0), _resistance(0.0), _voltage(0.0) {}
  Battery(double emf) : _emf(emf), _resistance(0.0), _voltage(emf) {}
  Battery(double emf, double res) : _emf(emf), _resistance(res) {
    _voltage = emf / res;
  }
  Battery(double emf, double res, double volt)
    : _emf(emf), _resistance(res), _voltage(volt) {}
private:
  double _emf;
  double _resistance;
  double _voltage;
};

class Resistor : public Component {
public:
  Resistor() : _resistance(0.0), _voltage(0.0), _current(0.0), _power(0.0) {}
  Resistor(double res, double volt, double current, double pwr)
    : _resistance(res), _voltage(volt), _current(current), _power(pwr) {}
  Resistor(double res)
    : _resistance(res), _voltage(0.0), _current(0.0), _power(0.0) {}
private:
  double _resistance;
  double _voltage;
  double _current;
  double _power;
};
#endif // !Components_h
