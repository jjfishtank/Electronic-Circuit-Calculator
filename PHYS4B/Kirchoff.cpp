#include <iostream>
#include "Circuit.h"
//#include <gmtl/gmtl.h>

using namespace std;

int main() {
  ifstream fin("circuit.txt");
  Circuit* circuit_1 = new Circuit(fin);
  cout << circuit_1->toString();







  /* Brainstorming KVL current implementation

  // ┌─ R1 ┬ R2 ─┐
  // V1    R3    V2
  // └─────┴─────┘

  auto V1 = 5;
  auto V2 = 2;
  auto R1 = 2000;
  auto R2 = 2000;
  auto R3 = 1000;

  // Loop 1: V1-R1-R3 / Current: I1
  // Loop 2: R3-R2-V2 / Current: I2

  auto I1 = -(R1 + R3);
  auto I2 = R3;
  gmtl::Matrix<int, 2, 3> a;*/

  return 0;
}
