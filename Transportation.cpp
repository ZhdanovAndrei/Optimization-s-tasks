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
    return allocations;
}


vector<Allocation> vogelApproximation(vector<int> supply, vector<int> demand, const vector<vector<int>>& cost) {
    vector<Allocation> allocations;
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
