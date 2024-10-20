#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<long double>> vvd;

vector<vector<long double>> add(vector<vector<long double>>A,vector<vector<long double>>B){
    if(A.size() != B.size() or A[0].size() != B[0].size()){
        return {{-1}};
    }
    vector<vector<long double>>Sum(A.size(), vector<long double>(A[0].size(), 0));
    for(int i = 0;i < (int)A.size();i++){
        for(int j = 0;j < (int)A[0].size();j++){
            Sum[i][j] = A[i][j] + B[i][j];      
        }
    }
    return Sum;
}

vector<vector<long double>> subtract(vector<vector<long double>>A,vector<vector<long double>>B){
    if(A.size() != B.size() or A[0].size() != B[0].size()){
        return {{-1}};
    }
    vector<vector<long double>>Sum(A.size(), vector<long double>(A[0].size(), 0));
    for(int i = 0;i < (int)A.size();i++){
        for(int j = 0;j < (int)A[0].size();j++){
            Sum[i][j] = A[i][j] - B[i][j];      
        }
    }
    return Sum;
}

vector<vector<long double>> mul(vector<vector<long double>>A,vector<vector<long double>>B){
    if(A[0].size() != B.size()){
        return {{}};
    }
    vector<vector<long double>>Prod(A.size(), vector<long double>(B[0].size(), 0));
    for(int i = 0;i < (int)A.size();i++){
        for(int j = 0;j < (int)B[0].size();j++){
            for(int k = 0;k < A[0].size();k++){
                Prod[i][j] += A[i][k] * B[k][j];
            }      
        }
    }
    return Prod;
}

vector<vector<long double>>transpose(vector<vector<long double>>A){
    vector<vector<long double>>T(A[0].size(), vector<long double>(A.size(),0));
    for(int i = 0;i < A.size();i++){
        for(int j = 0;j < A[0].size();j++){
            T[j][i] = A[i][j];
        }
    }
    return T;
}

vector<vector<long double>>divByScalar(vector<vector<long double>>A, long double c){
    if(c == 0){
        return {{}};
    }
    for(int i = 0;i < A.size();i++){
        for(int j = 0;j < A[0].size();j++){
            A[i][j] /= c;
        }
    }
    return A;
}

vector<vector<long double>>mulByScalar(vector<vector<long double>>A, long double c){
    for(int i = 0;i < A.size();i++){
        for(int j = 0;j < A[0].size();j++){
            A[i][j] *= c;
        }
    }
    return A;
}

vector<vector<long double>>minMatrix(vector<vector<long double>>&A, int x,int y){
    int n = A.size();
    int m = A[0].size();
    vector<vector<long double>>B;
    for(int i = 0;i < n;i++){
        if(i == x) continue;
        B.push_back({});
        for(int j = 0;j < m;j++){
            if(j == y) continue;
            B.back().push_back(A[i][j]);
        }
    }
    return B;
}

long double det(vector<vector<long double>>A){
    long double ans = 0;
    int n = A.size();
    if(A.size() == 1) return A[0][0];
    int sign = 1;
    for(int j = 0;j < n;j++){
        ans += sign * A[0][j] * det(minMatrix(A,0,j));
        sign *= -1;
    }
    return ans;
}

vector<vector<long double>>adjointMatrix(vector<vector<long double>>A){
    int n = A.size();
    if(n == 1) return {{1}};
    vector<vector<long double>>ans(n,vector<long double>(n));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            int sign = 1;
            if((i+j)%2) sign = -1;
            ans[i][j] = sign * det(minMatrix(A,i,j));
        }
    }
    return transpose(ans);
}

vector<vector<long double>>inverseMatrix(vector<vector<long double>>A){
    int n = A.size();
    vector<vector<long double>>inv = adjointMatrix(A);
    inv = divByScalar(inv,det(A));
    return inv;
}


void printMatrix(vector<vector<long double>>A){
    for(int i = 0;i < (int)A.size();i++){
        for(int j = 0;j < (int)A[0].size();j++){
            cout<<A[i][j]<<' ';
        }
        cout<<'\n';
    }
}

vvd make_D_matrix(vvd x) {
    int n = x.size();
    vector<vector<long double>> matrix(n, vector<long double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        matrix[i][i] = x[i][0];
    }
    return matrix;
}

long double alpha = 0.5;

vvd iteration(vvd x, vvd A, vvd c, vvd I) {
    int n = x.size();
    vvd D = make_D_matrix(x);
    vvd Aq = mul(A, D);
    vvd cq = mul(D, c);
    vvd Aqt = transpose(Aq);
    vvd AqAqt = mul(Aq, Aqt);
    vvd IAqAqt = inverseMatrix(AqAqt);
    vvd AqtIAqAqt = mul(Aqt, IAqAqt);
    vvd AqtIAqAqtAq = mul(AqtIAqAqt, Aq);
    vvd P = subtract(I, AqtIAqAqtAq);
    vvd cp = mul(P, cq);

    long double v = 0;
    for (int i = 0; i < cp.size(); i++) {
        for (int j = 0; j < cp[i].size(); j++) {
            v = min(v, cp[i][j]);
        }
    }
    v = abs(v);
    // printf("%f\n", v);

    vvd O(n, vector<long double>(1, 1.0));
    vvd TM = mulByScalar(cp, alpha / v);
    vvd xq = add(O, TM);

    vvd result_x = mul(D, xq);
    return result_x;
} 

const long double eps = 1e-6;

vvd ipalgo(vvd x, vvd A, vvd c) {
    int n = x.size();
    vvd I(n, vector<long double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        I[i][i] = 1.0;
    }
    while (true) {
        vvd xnew = iteration(x, A, c, I);
        bool flag = true;
        for (int i = 0; i < x.size(); i++) {
            for (int j = 0; j < x[i].size(); j++) {
                if (abs(xnew[i][j] - x[i][j]) > eps) {
                    flag = false;
                }
            }
        }
        if (flag) {
            break;
        }
        x = xnew;
        // printMatrix(xnew);
        // cout << endl;
    }
    // printMatrix(x);
    return x;
}

int main() {
    vector<vector<long double>>A = {
        {18, 15, 12, 1, 0, 0},
        {6, 4, 8, 0, 1, 0},
        {5, 3, 3, 0, 0, 1}
    };
    vvd x = {
        {1}, {1}, {1}, {315}, {174}, {169}
    };
    vvd c = {
        {9}, {10}, {16}, {0}, {0}, {0}
    };
    vvd xans_f = ipalgo(x, A, c);
    printMatrix(xans_f);
    printMatrix(mul(transpose(xans_f), c));

    cout<<"\n\n";

    alpha = 0.9;
    vvd xans_s = ipalgo(x, A, c);
    printMatrix(xans_s);
    printMatrix(mul(transpose(xans_s), c));
}