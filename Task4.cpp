#include <bits/stdc++.h>

#define double long double

using namespace std;

double func2(double x) {
    double tmp = x - 2;
    return tmp * tmp + 3;
}

vector<pair<double, double>> goldenSectionMethod(double (*func)(double), double xl, double xr, double e) {
    vector<pair<double,double>> iterations;
    double golden_ratio = (sqrt(5 + 0.0) - 1) / 2.0;
    while (abs(xl - xr) >= e) {
        double x1 = xr - golden_ratio * (xr - xl);
        double x2 = xl + golden_ratio * (xr - xl);
        if (func(x1) > func(x2)) {
            xl = x1;
        } else {
            xr = x2;
        }
        iterations.push_back({xl, xr});
    }
    return iterations;
}

void print_iterations(string methodName, vector<pair<double, double>> iterations) {
    cout << "--------------------------------------------------------------" << endl;
    cout << methodName << endl;
    int number = 0;
    for (auto i : iterations) {
        number++;
        cout << "Iteration #" << setw(2) << number << "   =>   Xl: " << i.first << " Xr: " << i.second << endl;
    }
    cout << endl << endl;
}

int main() {
    vector<pair<double, double>> iterations2 = goldenSectionMethod(func2, 0, 5, 1e-4);
    print_iterations("Golden Section Method", iterations2);
}
