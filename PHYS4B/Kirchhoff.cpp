// Jeremy Renati
// Kirchhoff

#include "Circuit.h"
#include <iostream>


using namespace std;

void ManualMeshAnalysis() {
  /*
    ┌ R1 ┬ R2 ┬ R3 ┐
    │    R4    R5   R6
    └ V1 ┴────┴ V2 ┘
     -  +      -  +
  */

  double R1 = 5;
  double R2 = 10;
  double R3 = 3;
  double R4 = 7;
  double R5 = 4;
  double R6 = 1;
  double V1 = 1;
  double V2 = 3;

  /*
  Mesh 1: V1-R1-R4 Loop
  Mesh 2: R4-R2-R5 Loop
  Mesh 3: V2-R5-R3-R6 Loop

  Mesh Currents (all clockwise)
  I1 for Mesh 1
  I2 for Mesh 2
  I3 for Mesh 3
  */

  Eigen::Matrix<double, 3, 3> A {
    { R1 + R4, -R4, 0 },
    { -R4, R2 + R4 + R5, -R5 },
    { 0, -R5, R3 + R5 + R6 }
  };
  Eigen::Matrix<double, 3, 1> B { -V1, 0 , -V2 };

  cout << "Matrix A:\n" << A << endl;
  cout << "Matrix B:\n" << B << endl;

  cout << "Computing System...\n" << endl;
  // Eigen linear solver
  Eigen::Matrix<double, 1, 3> X = A.colPivHouseholderQr().solve(B);

  cout << "Solution: \n";
  cout << "I1 = " << X[0] << ", I2 = " << X[1] << ", I3 = " << X[2] << endl;
}

void ManualNodalAnalysis() {
  /*
  Electronic Circuit is
    ┌───┬ R3 ┬───┐
  ↑ I1  R1   R2  I2 ↓
    └───┴─┬──┴───┘
          ⏚
  */

  double R1 = 4;
  double R2 = 10;
  double R3 = 6;
  double I1 = 1;
  double I2 = 2;

  /*
  Node 0: Connecting I1-R1-R2-I2 (node at the bottom)
  Node A: Connecting I1-R1-R3    (upper left node)
  Node B: Connecting I2-R2-R3    (upper right node)
  */

  Eigen::Matrix<double, 2, 2> A{
    { 1 / R1 + 1 / R3, -(1 / R3) },
    { -(1 / R3), 1 / R2 + 1 / R3 },
  };
  Eigen::Matrix<double, 2, 1> B{ I1, -I2 };


  cout << "Matrix A:\n" << A << endl;
  cout << "Matrix B:\n" << B << endl;

  cout << "Computing System...\n" << endl;
  // Eigen linear solver
  Eigen::Matrix<double, 1, 2> X = A.colPivHouseholderQr().solve(B);

  cout << "Solution: \n";
  cout << "Va = " << X[0] << ", Vb = " << X[1] << endl;
}

int main() {
  ifstream fin("circuit.txt");
  Circuit* circuit_1 = new Circuit(fin);
  cout << "Circuit\n";
  cout << circuit_1->toString();

  cout << "\nCircuit Info\n";
  cout << "Component count: " << circuit_1->component_count() << endl;
  cout << "Voltage count: " << circuit_1->voltage_count() << endl;
  cout << "Current count: " << circuit_1->current_count() << endl;
  cout << "Resistor count: " << circuit_1->resistor_count() << endl;
  cout << "Node count: " << circuit_1->nodes_count() << endl << endl;
  cout << "Matrix A:\n" << circuit_1->A_matrix() << endl;
  cout << "Matrix B:\n" << circuit_1->b_matrix() << endl;
  
  /*
  cout << "\nNodes list:\n";
  for (auto i : circuit_1->nodes()) {
    cout << '\"' << i.first << "\" : " << i.second << endl;
  }
  */

  /* manual nodal/mesh analysis
  cout << endl;
  ManualMeshAnalysis();
  cout << endl;
  ManualNodalAnalysis();
  */

  return 0;
}