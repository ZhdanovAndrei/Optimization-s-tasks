#include <bits/stdc++.h>

#define double long double

using namespace std;

double func(double x) {
    return x*x*x-6*x*x+11*x-6;
}

double BisectionMethod(double (*func)(double), double xl, double xr, double e) {
    while (abs(func((xl+xr)/2)) >= e) {
        double x1 = 0.5*(xr+xl-e);
        double x2 = 0.5*(xr+xl+e);
        if (func(xl) > 0 and func(x2) < 0) {
            xr = x2;
        } else {
            xl = x1;
        }
    }
    return (xl+xr)/2;
}

int main() {
    double x_root = BisectionMethod(func, 1, 2, 1e-6);
    cout<<x_root; // 2 for this function this and interval [1,2]
}
