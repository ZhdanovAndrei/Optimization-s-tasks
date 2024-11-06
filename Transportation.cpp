#include <iostream>
#include <vector>

using namespace std;

struct Allocation {
    int source;
    int destination;
    int amount;
};


bool isBalanced(const vector<int>& supply, const vector<int>& demand) {
   
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
    return allocations;
}


void printAllocations(const vector<Allocation>& allocations) {
    for (const auto& allocation : allocations) {
        cout << "(S" << allocation.source + 1 << ", D" << allocation.destination + 1 
             << ", " << allocation.amount << ")" << endl;
    }
}


int main() {
    vector<int> supply = {20, 25, 25};
    vector<int> demand = {15, 15, 30, 10};
    vector<vector<int>> cost = {
        {8, 6, 10, 3},
        {9, 12, 13, 6},
        {14, 9, 16, 9}
    };

    if (!isBalanced(supply, demand)) {
        cout << "The problem is not balanced!" << endl;
        return 0;
    }
    
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
