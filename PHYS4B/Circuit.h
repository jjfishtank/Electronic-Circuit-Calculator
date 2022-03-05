// Jeremy Renati
// Electronic Circuit Simulation

#include "Components.h"
#include <vector>

#ifndef Circuit_h
#define Circuit_h

class Circuit {
  Circuit() {
    _components = vector<Component*>(MAX_COMPONENTS, new Component);
  }
private:
  static const int MAX_COMPONENTS;
  vector<Component*> _components;
};

const int Circuit::MAX_COMPONENTS = 999;

#endif // !Circuit_h
