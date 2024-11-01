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

    // Objective Functions

    vvd ObjectiveFunction1 = {
        {9}, {10}, {16}, {0}, {0}, {0}
    };

    vvd ObjectiveFunction2 = {
        {8}, {12}, {14}, {1}, {0}, {0}
    };

    vvd ObjectiveFunction3 = {
        {11}, {13}, {15}, {0}, {1}, {0}
    };

    vvd ObjectiveFunction4 = {
        {7}, {9}, {13}, {2}, {0}, {0}
    };
    
    vvd ObjectiveFunction5 = {
        {10}, {14}, {12}, {3}, {1}, {0}
    };

    // Constraints

    vector<vector<long double>> ConstraintFunction1 = {
        {18, 15, 12, 1, 0, 0},
        {6, 4, 8, 0, 1, 0},
        {5, 3, 3, 0, 0, 1}
    };

    vector<vector<long double>> ConstraintFunction2 = {
        {20, 10, 15, 1, 0, 0},
        {7, 5, 9, 0, 1, 0},
        {4, 6, 2, 0, 0, 1}
    };

    vector<vector<long double>> ConstraintFunction3 = {
        {25, 20, 10, 1, 0, 0},
        {8, 6, 7, 0, 1, 0},
        {3, 5, 4, 0, 0, 1}
    };

    vector<vector<long double>> ConstraintFunction4 = {
        {15, 25, 20, 1, 0, 0},
        {9, 7, 5, 0, 1, 0},
        {6, 4, 3, 0, 0, 1}
    };

    vector<vector<long double>> ConstraintFunction5 = {
        {30, 18, 22, 1, 0, 0},
        {10, 12, 6, 0, 1, 0},
        {5, 8, 4, 0, 0, 1}
    };

    // Initial Feasible Solution Values

    vvd InitialSolution1 = {
        {1}, {1}, {1}, {315}, {174}, {169}
    };

    vvd InitialSolution2 = {
        {2}, {2}, {2}, {200}, {150}, {120}
    };

    vvd InitialSolution3 = {
        {3}, {2}, {1}, {250}, {180}, {160}
    };

    vvd InitialSolution4 = {
        {2}, {3}, {2}, {300}, {160}, {140}
    };

    vvd InitialSolution5 = {
        {4}, {1}, {3}, {400}, {200}, {180}
    };

    alpha = 0.9;

    cout<<"\nProblem 1:\n";

    vvd xans_f1 = ipalgo(InitialSolution1, ConstraintFunction1, ObjectiveFunction1);
    printMatrix(xans_f1);
    printMatrix(mul(transpose(xans_f1), ObjectiveFunction1));

    cout<<"------------------------------\n\n";

    vvd xans_s1 = ipalgo(InitialSolution1, ConstraintFunction1, ObjectiveFunction1);
    printMatrix(xans_s1);
    printMatrix(mul(transpose(xans_s1), ObjectiveFunction1));

    cout<<"\nProblem 2:\n";

    vvd xans_f2 = ipalgo(InitialSolution2, ConstraintFunction2, ObjectiveFunction2);
    printMatrix(xans_f2);
    printMatrix(mul(transpose(xans_f2), ObjectiveFunction2));

    cout<<"------------------------------\n\n";

    vvd xans_s2 = ipalgo(InitialSolution2, ConstraintFunction2, ObjectiveFunction2);
    printMatrix(xans_s2);
    printMatrix(mul(transpose(xans_s2), ObjectiveFunction2));
    
    cout<<"\nProblem 3:\n";

    vvd xans_f3 = ipalgo(InitialSolution3, ConstraintFunction3, ObjectiveFunction3);
    printMatrix(xans_f3);
    printMatrix(mul(transpose(xans_f3), ObjectiveFunction3));

    cout<<"------------------------------\n\n";

    vvd xans_s3 = ipalgo(InitialSolution3, ConstraintFunction3, ObjectiveFunction3);
    printMatrix(xans_s3);
    printMatrix(mul(transpose(xans_s3), ObjectiveFunction3));
    
    cout<<"\nProblem 4:\n";

    vvd xans_f4 = ipalgo(InitialSolution4, ConstraintFunction4, ObjectiveFunction4);
    printMatrix(xans_f4);
    printMatrix(mul(transpose(xans_f4), ObjectiveFunction4));

    cout<<"------------------------------\n\n";

    vvd xans_s4 = ipalgo(InitialSolution4, ConstraintFunction4, ObjectiveFunction4);
    printMatrix(xans_s4);
    printMatrix(mul(transpose(xans_s4), ObjectiveFunction4));
    
    cout<<"\nProblem 5:\n";

    vvd xans_f5 = ipalgo(InitialSolution5, ConstraintFunction5, ObjectiveFunction5);
    printMatrix(xans_f5);
    printMatrix(mul(transpose(xans_f5), ObjectiveFunction5));

    cout<<"------------------------------\n\n";

    vvd xans_s5 = ipalgo(InitialSolution5, ConstraintFunction5, ObjectiveFunction5);
    printMatrix(xans_s5);
    printMatrix(mul(transpose(xans_s5), ObjectiveFunction5));

}