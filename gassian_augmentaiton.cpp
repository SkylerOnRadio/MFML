#include <iostream>
#include <vector>

int getPosOfPivot(std::vector<int> eqn) {
  int i = 0;
  for (int val : eqn) {
    if (val != 0)
      return i;
    else
      ++i;
  }

  return -1;
}

std::vector<std::vector<int>>
getRowEchelonForm(std::vector<std::vector<int>> matrix, int eqns, int vars) {

  for (int i = 0; i < eqns; ++i) {
    int pivotPos = getPosOfPivot(matrix.at(i));

    if (pivotPos == -1)
      continue;

    for (int j = i + 1; j < eqns; ++j) {
      std::vector<int> &pivotEqn = matrix.at(i);
      std::vector<int> &targetEqn = matrix.at(j);

      int coef = -(targetEqn.at(pivotPos) / pivotEqn.at(pivotPos));

      for (int k = 0; k < vars + 1; ++k) {
        targetEqn.at(k) = targetEqn.at(k) + (coef * pivotEqn.at(k));
      }
    }
  }

  return matrix;
}

int main() {
  int numOfVars{0};
  int numOfEqns{0};
  std::vector<std::vector<int>> matrix;

  std::cout << "Enter the number of variables: ";
  std::cin >> numOfVars;

  std::cout << "Enter the number of equations: ";
  std::cin >> numOfEqns;

  std::cout << "Enter the coefficients of the variables.\n";
  std::cout << "Eg. For 3x + 4y - 5z = 4\n";
  std::cout << "Input > 3 4 -5\n";

  for (int i = 0; i < numOfEqns; ++i) {
    std::vector<int> eqn;

    for (int j = 0; j < numOfEqns; ++j) {
      int coef{0};
      std::cin >> coef;
      eqn.push_back(coef);
    }

    matrix.push_back(eqn);
  }

  std::cout << "Enter the result of the equations.\n";
  std::cout << "Eg. For 3x + 4y - 5z = 4\n";
  std::cout << "Input > 4\n";

  for (auto &eqn : matrix) {
    int result{0};
    std::cin >> result;

    eqn.push_back(result);
  }

  for (auto eqn : matrix) {
    for (int val : eqn) {
      std::cout << val << " ";
    }
    std::cout << "\n";
  }

  matrix = getRowEchelonForm(matrix, numOfEqns, numOfVars);

  for (auto eqn : matrix) {
    for (int val : eqn) {
      std::cout << val << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
