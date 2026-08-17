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

// maxCol is needed since we need the rank of the augemented matrix and the
// original co-efficient matrix
int getRank(std::vector<std::vector<int>> matrix, int maxCol) {
  int rank{0};
  for (auto row : matrix) {
    bool independent{false};
    for (int i = 0; i < maxCol; ++i) {
      if (row.at(i) != 0)
        independent = true;
    }

    if (independent)
      ++rank;
  }

  return rank;
}

int typeOfSolution(int augRank, int coefRank, int vars) {
  if (augRank < coefRank)
    return 0;
  else if (augRank == coefRank) {
    if (augRank < vars)
      return 1;
    else if (augRank == vars)
      return 2;
  }
  return -1;
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

  // std::cout << "\n";
  // for (auto eqn : matrix) {
  //   for (int val : eqn) {
  //     std::cout << val << " ";
  //   }
  //   std::cout << "\n";
  // }
  // std::cout << "\n";

  int coefRank = getRank(matrix, numOfVars);
  matrix = getRowEchelonForm(matrix, numOfEqns, numOfVars);
  int augRank = getRank(matrix, numOfVars + 1);

  // for (auto eqn : matrix) {
  //   for (int val : eqn) {
  //     std::cout << val << " ";
  //   }
  //   std::cout << "\n";
  // }

  int solutionType = typeOfSolution(augRank, coefRank, numOfVars);

  if (solutionType != 2) {
    if (solutionType == -1) {
      std::cout << "There is something wrong!\n";
      return 0;
    }

    std::cout << (solutionType == 0 ? "There is no solution!"
                                    : "There are infinite solutions!")
              << "\n";

    return 0;
  }

  return 0;
}
