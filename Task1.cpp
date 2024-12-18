#include <bits/stdc++.h>

using namespace std;

int calcAccuracy(double number) {
    int cnt = 0;
    while (number < 1) {
        number *= 10;
        cnt++;
    }
    return cnt;
}

void printMatrix(vector<vector<double>> &A) {
    for (auto & i : A) {
        for (double j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}

int findIndexOfMinimum(vector<double> &A) {
    int ind = 0;
    for (int i = 0; i < A.size(); i++) {
        if (A[i] < A[ind]) ind = i;
    }
    if (A[ind] < 0) return ind;
    return -1;
}

int findRowWithMinimumRatio(vector<vector<double>> &table, int col) {
    vector<pair<double,int>> v;
    for (int i = 0; i < table.size() - 1; i++) {
        if (table[i][col] == 0.0) continue;
        double ratio = table[i].back() / table[i][col];
        if (ratio >= 0.0) {
            v.emplace_back(ratio, i);
        }
    }
    sort(v.begin(), v.end());
    if (v.empty()) return -1;
    return v[0].second;
}

int problemNumber = 0;

void SimplexMethod(vector<double> C, vector<vector<double>> A, vector<double> b, double approximationAccuracy) {
    problemNumber++;
    int accuracyCnt = calcAccuracy(approximationAccuracy);
    cout << fixed << setprecision(accuracyCnt);
    vector<vector<double>> table;
    for (int i = 0; i < A.size(); i++) {
        table.push_back(A[i]);
        while (table[i].size() < C.size() + A.size()) {
            if (table[i].size() - A[i].size() == i) table[i].push_back(1.0);
            else table[i].push_back(0.0);
        }
        table[i].push_back(b[i]);
    }
    int ind = (int) table.size();
    if (!table.empty()) {
        table.push_back(C);
        for (int i = 0; i < table[0].size(); i++) {
            if (i < C.size()) table[ind][i] *= -1;
            else table[ind].push_back(0.0);
        }
    }
    vector<int> xx((int) C.size(), -1);
    vector<double> xval((int) C.size(), 0.0);
    while (true) {
        int col = findIndexOfMinimum(table[ind]);
        if (col == -1) break;
        int row = findRowWithMinimumRatio(table, col);
        if (row == -1) break;

        double value = table[row][col];
        for (auto &i : table[row]) {
            i /= value;
        }

        for (int i = 0; i < table.size(); i++) {
            if (i == row) continue;
            double coefficient = -table[i][col];
            for (int j = 0; j < table[i].size(); j++) {
                table[i][j] += coefficient * table[row][j];
            }
        }

        if (col < xx.size()) xx[col] = row;
    }
    for (int i = 0; i < xx.size(); i++) {
        if (xx[i] == -1) continue;
        xval[i] = table[xx[i]].back();
    }

    cout << "Problem #" << problemNumber << endl;
    cout << "X - [";
    for (int i = 0; i < xval.size(); i++) {
        cout << xval[i];
        if (i != (int)xval.size() - 1) cout << ", ";
    }
    cout << "]" << endl << "Result: " << table.back().back() << endl << endl;
}

int main() {
    double accuracy = 0.0001;
    vector<double> coeffObj1 = {4, 9};
    vector<vector<double>> coeffContrain1 = {
            {2, 0},
            {2, 3},
            {5, 1}
    };
    vector<double> Rhs1 = {8, 16, 20};
    SimplexMethod(coeffObj1, coeffContrain1, Rhs1, accuracy);


    vector<double> coeffObj2 = {4, 1};
    vector<vector<double>> coeffContrain2 = {
            {2, -1},
            {10, 7}
    };
    vector<double> Rhs2 = {13, 100};
    SimplexMethod(coeffObj2, coeffContrain2, Rhs2, accuracy);

    vector<double> coeffObj3 = {2, 8};
    vector<vector<double>> coeffContrain3 = {
            {2, -3},
            {-4, 10}
    };
    vector<double> Rhs3 = {40, 40};
    SimplexMethod(coeffObj3, coeffContrain3, Rhs3, accuracy);

    vector<double> coeffObj4 = {-2, 4};
    vector<vector<double>> coeffContrain4 = {
            {2, 1},
            {-4, 10},
            {-2, 1}
    };
    vector<double> Rhs4 = {79, 53,-10};
    SimplexMethod(coeffObj4, coeffContrain4, Rhs4, accuracy);

    vector<double> coeffObj5 = {2.5, 2.5};
    vector<vector<double>> coeffContrain5 = {
            {10, 0},
            {0, 10},
            {1, -1},
            {-1, 1}

    };
    vector<double> Rhs5 = {100, 100, 5, 5};
    SimplexMethod(coeffObj5, coeffContrain5, Rhs5, accuracy);

    return 0;
}

/*

Problem #1
X - [0.0000, 5.3333]
Result: 48.0000

Problem #2
X - [7.9583, 2.9167]
Result: 34.7500

Problem #3
X - [65.0000, 30.0000]
Result: 370.0000

Problem #4
X - [0.0000, 5.3000]
Result: 21.2000

Problem #5
X - [10.0000, 10.0000]
Result: 50.0000

 */