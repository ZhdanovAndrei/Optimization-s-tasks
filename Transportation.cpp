#include <iostream>
#include <vector>
#include<array>

using namespace std;

struct Allocation {
    int source;
    int destination;
    int amount;
};

bool NotIn (int index, vector<int> list){
    for(int i = 0; i < list.size(); i++){
        if (index == list[i]){
            return false;
        }
    }
    return true;
}
void printTable(vector<int> supply, vector<int> demand, const vector<vector<int>>& cost){
    int inputTable[4][5];
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 5; j++){

            if (i == 3 && j == 4){
                inputTable[i][j] = 0;
            }
            else if (i < 3 && j < 4){
                inputTable[i][j] = cost[i][j]; 
            }
            else if (i == 3){
            
                inputTable[i][j] = demand[j];
            }
            else if (j == 4){
                inputTable[i][j] = supply[i];
            }
        }
    }
    cout << "input Table:" << endl;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 5; j++){
            cout << inputTable[i][j] << " ";
        }
        cout << endl;
    }
}

bool isBalanced(const vector<int>& supply, const vector<int>& demand) {
   int sumSupply = 0;
   int sumDemand = 0;
   for (int i = 0; i < supply.size(); i++){
    sumSupply += supply[i];
   }
   for (int i = 0; i < demand.size(); i++){
    sumDemand += demand[i];
   }
   return (sumDemand == sumSupply);
}

vector<Allocation> northWestCorner(vector<int> supply, vector<int> demand, const vector<vector<int>>& cost) {
    vector<Allocation> allocations;
    int row = 0, col = 0;
    while (row < cost.size() && col < cost[0].size()) {
        int amount = min(supply[row], demand[col]);
        supply[row] -= amount;
        demand[col] -= amount;
        allocations.push_back({row, col, amount});
        if (supply[row] > demand[col]) {
            col++;
        } else if (supply[row] < demand[col]) {
            row++;
        } else {
            row++;
            col++;
        }
    }
    return allocations;
}


vector<Allocation> vogelApproximation(vector<int> supply, vector<int> demand, const vector<vector<int>>& cost) {
    vector<Allocation> allocations;
    int n = (int)supply.size();
    int m = (int)demand.size();
    vector<int>remaining_rows;
    vector<int>remaining_columns;
    for(int i = 0;i < n;i++) remaining_rows.push_back(i);
    for(int i = 0;i < m;i++) remaining_columns.push_back(i);
    while(n > 1 and m > 1){
        // cout<<"\nRemaining rows: ";
        // for(int i = 0;i < n;i++) cout<<remaining_rows[i]<<' ';
        // cout<<"\nRemaining columns: ";
        // for(int i = 0;i < m;i++) cout<<remaining_columns[i]<<' ';
        // cout<<'\n';
        int largest_difference = -1e9;
        int wh = 0; // row or column
        int idx = -1;
        for(int i = 0;i < n;i++){
            int mn = 1e9;
            int smn = 1e9;
            for(int j = 0;j < m;j++){
                int val = cost[remaining_rows[i]][remaining_columns[j]];
                if(val < mn){
                    smn = mn;
                    mn = val;
                }
                else if(val < smn){
                    smn = val;
                }
            }
            if(largest_difference < smn - mn){
                largest_difference = smn - mn;
                wh = 1;
                idx = i;
            }
        }
        for(int j = 0;j < m;j++){
            int mn = 1e9;
            int smn = 1e9;
            for(int i = 0;i < n;i++){
                int val = cost[remaining_rows[i]][remaining_columns[j]];
                if(val < mn){
                    smn = mn;
                    mn = val;
                }
                else if(val < smn){
                    smn = val;
                }
            }
            if(largest_difference < smn - mn){
                largest_difference = smn - mn;
                wh = 2;
                idx = j;
            }
        }
        int row = -1;
        int col = -1;
        if(wh == 1){
            row = idx;
            int mn = 1e9;
            for(int j = 0;j < m;j++){
                if(mn > cost[remaining_rows[idx]][remaining_columns[j]]){
                    mn = cost[remaining_rows[idx]][remaining_columns[j]];
                    col = j;
                }
            }
        }
        else {
            col = idx;
            int mn = 1e9;
            for(int i = 0;i < n;i++){
                if(mn > cost[remaining_rows[i]][remaining_columns[idx]]){
                    mn = cost[remaining_rows[i]][remaining_columns[idx]];
                    row = i;
                }
            }
        }
        Allocation now;
        now.source = remaining_rows[row];
        now.destination = remaining_columns[col];
        now.amount = min(supply[remaining_rows[row]], demand[remaining_columns[col]]);
        allocations.push_back(now);

        supply[remaining_rows[row]] -= now.amount;
        demand[remaining_columns[col]] -= now.amount;
        if(supply[remaining_rows[row]] == 0){
            remaining_rows.erase(remaining_rows.begin() + row);
            n--;
        }
        else {
            remaining_columns.erase(remaining_columns.begin() + col);
            m--;
        }
    }
    if(n == 1){
        for(int j = 0;j < m;j++){
            Allocation now;
            now.source = remaining_rows[0];
            now.destination = remaining_columns[j];
            now.amount = min(supply[remaining_rows[0]], demand[remaining_columns[j]]);
            allocations.push_back(now);
        }
    }
    else {
        for(int i = 0;i < n;i++){
            Allocation now;
            now.source = remaining_rows[i];
            now.destination = remaining_columns[0];
            now.amount = min(supply[remaining_rows[i]], demand[remaining_columns[0]]);
            allocations.push_back(now);
        }
    }
    return allocations;
}


vector<Allocation> russellApproximation(vector<int> supply, vector<int> demand, const vector<vector<int>>& cost) {
    vector<Allocation> allocations;
    int totalSum = 0;
    vector<int> I = {};
    vector<int> J = {};
    for (int i = 0; i < demand.size(); i++){
        totalSum += demand[i];
    }
    while (totalSum != 0){
        int maxRow[3] = {0,0,0};
        int maxColumn[4] = {0,0,0,0};
        for (int i = 0; i < 3; i++){
            int sum = 0;
            for (int j = 0; j < 4; j++){
                if (sum < cost[i][j] && NotIn(i, I) && NotIn(j, J)){
                    sum = cost[i][j];
                }
            }
            maxRow[i] = sum;
        }
         for (int j = 0; j < 4; j++){
            int sum = 0;
            for (int i = 0; i < 3; i++){
                if (sum < cost[i][j] && NotIn(i, I) && NotIn(j, J)){
                    sum = cost[i][j];
                }
            }
            maxColumn[j] = sum;
        }
        int minValue = 1000000;
        int minI = -1;
        int minJ = -1;
        int MinMatrix[3][4] = {{0,0,0,0}, {0,0,0,0} , {0,0,0,0}};
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 4; j++){
                if ((NotIn(i, I)) && (NotIn(j, J))){
                    MinMatrix[i][j] = cost[i][j] - (maxRow[i] + maxColumn[j]); 
                    if ((MinMatrix[i][j] < minValue)){
                        minValue = MinMatrix[i][j]; 
                        minI = i;
                        minJ = j;
                    }
                }
            }
        }
       
        int amount = min(demand[minJ], supply[minI]);
        totalSum -= amount;
        
        demand[minJ] -= amount;
        supply[minI] -= amount;
        if (demand[minJ] == 0){
            J.push_back(minJ);
        }
        if (supply[minI] == 0){
            I.push_back(minI);
        }
        Allocation location = {minI, minJ, amount};
        allocations.push_back(location);
        
    }
    
    return allocations;
}


void printAllocations(const vector<Allocation>& allocations) {
    for (const auto& allocation : allocations) {
        cout << "(S" << allocation.source + 1 << ", D" << allocation.destination + 1 
             << ", " << allocation.amount << ")" << endl;
    }
}


int main() {
    vector<int> supply = {7, 9, 18};
    vector<int> demand = {5, 8, 7, 14};

   

    vector<vector<int>> cost = {
        {19, 30, 50, 10},
        {70, 30, 40, 60},
        {40, 8, 70, 20}
    };

    if (!isBalanced(supply, demand)) {
        cout << "The problem is not balanced!" << endl;
        return 0;
    }
    
    printTable(supply, demand, cost);

    cout << "North-West Corner Method:" << endl;
    auto nwAllocations = northWestCorner(supply, demand, cost);
    printAllocations(nwAllocations);

    cout << "\nVogel's Approximation Method:" << endl;
    auto vogelAllocations = vogelApproximation(supply, demand, cost);
    printAllocations(vogelAllocations);

    cout << "\nRussell's Approximation Method:" << endl;
    auto russellAllocations = russellApproximation(supply, demand, cost);
    printAllocations(russellAllocations);

    return 0;
}
