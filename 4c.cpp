#include <iostream>
using namespace std;

double f(double x){
    return -x*x+4*x+1;
}

double der_f(double x){
    return -2*x+4;
}

const int maxn=1e6+5;
int N; // number of iterations
double a; // learing rate
double X[maxn]; // values of X in each iteration

int main(){


    // For X[0] = 0, a = 0.1, N = 100 --> the answer is X = 2, F(x) = 5
    // The smaller the a is the closer to the actual answer we get.

    // X[k+1] = X[k] + r[k] * der_f(X[k])
    cin >> X[0] >> a >> N;
    for(int i = 0;i < N;i++){
        double grad = der_f(X[i]);
        double r = (2 - X[i])/grad;
        X[i + 1] = X[i] + r * grad; 
        if(abs(der_f(X[i + 1])) <= a){
            cout<<X[i + 1]<<' '<<f(X[i+1]);
            return 0;
        }
    }
    cout<<X[N]<<' '<<f(X[N]);
}