#include <iostream>
#include <vector>
#include <algorithm> // for any_of
#include <cfloat>
#include <iomanip>

using namespace std;

double Simplex(vector<double> &coeffObj,
               vector<vector<double>> &coeffContrain,
               vector<double> &Rhs, double accuracy) {
  int countAccuracy = 0;
  while (accuracy != 1){
    accuracy *= 10;
    countAccuracy++;
  }
  cout << fixed << showpoint;
  cout << setprecision(countAccuracy);

  double sol = 0;
  vector<double *> decision(coeffObj.size(), nullptr);
  int ct = 0;
  for (size_t i = 0; i < coeffContrain.size(); ++i) {
    coeffObj.push_back(0);
  }

  for (double &i : coeffObj) {
    i = i * -1;
  }

  for (auto &row : coeffContrain) {
    for (size_t i = 0; i < coeffContrain.size(); ++i) {
      row.push_back((i == ct) ? 1.0 : 0.0);
    }
    ct++;
  }

  while (any_of(coeffObj.begin(), coeffObj.end(), [](double t) { return t < 0; })) {
    double minValue = 0;
    size_t indexMin = 0;

    for (size_t i = 0; i < coeffObj.size(); ++i) {
      if (coeffObj[i] < minValue) {
        indexMin = i;
        minValue = coeffObj[i];
      }
    }
    size_t indexRatio = 0;
    auto minRatio = DBL_MAX;
    for (size_t i = 0; i < Rhs.size(); ++i) {
      if (coeffContrain[i][indexMin] != 0) {
        double ratio = Rhs[i] / coeffContrain[i][indexMin];
        if (ratio > 0 && ratio < minRatio) {
          minRatio = ratio;
          indexRatio = i;
        }
      }
    }

    double value = coeffContrain[indexRatio][indexMin];
    Rhs[indexRatio] /= value;
    decision[indexMin] = &Rhs[indexRatio];
    for (double &i : coeffContrain[indexRatio]) {
      i /= value;
    }
    sol -= Rhs[indexRatio] * coeffObj[indexMin];
    for (size_t i = 0; i < coeffContrain.size(); ++i) {
      if (i != indexRatio) {
        double factor = coeffContrain[i][indexMin];
        Rhs[i] -= Rhs[indexRatio] * factor;

        for (size_t j = 0; j < coeffContrain[i].size(); ++j) {
          coeffContrain[i][j] -= coeffContrain[indexRatio][j] * factor;
        }
      }
    }
    double factorObj = coeffObj[indexMin];
    for (size_t i = 0; i < coeffObj.size(); ++i) {
      coeffObj[i] -= coeffContrain[indexRatio][i] * factorObj;
    }
  }
  for (int i = 0; i < decision.size(); ++i) {
    if (decision[i] != nullptr) {
      cout << "x" << i + 1 << " = " << *decision[i] << " ";
    } else {
      cout << "x" << i + 1 << " = " << 0 << " ";
    }
  }
  cout << "F = " << sol;
  return sol;
}

int main() {
  vector<double> coeffObj = {5, 4};
  vector<vector<double>> coeffContrain = {
      {6, 4},
      {1, 2},
      {-1, 1},
      {0, 1}
  };
  vector<double> Rhs = {24, 6, 1, 2};
  double accuracy = 0.0001;
  double sol = Simplex(coeffObj, coeffContrain, Rhs, accuracy);

  return 0;
}