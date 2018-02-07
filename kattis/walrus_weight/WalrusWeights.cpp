#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <map>
#include <set>
#include <queue>

using namespace std;



struct knapSack {
    knapSack () {};
    
    vector<int> knapsack(int capacity, vector<pair<int, int> > items) {
        //itemList stores the value and then the weight in the pair.
        int table[items.size() + 1][capacity + 1];
        
        //build table
        for(int i = 0; i <= items.size(); ++i) {
            //Adjustments because table is +1 larger in row then nr of items.
            pair<int, int> currItem;
            if(i>0) {
                currItem = items[i-1];
            }
            
            for(int j = 0; j <= capacity; ++j) {
                if(i == 0 || j == 0) {
                    table[i][j] = 0;
                }
                
                //weight less than weight of item
                else if(j < currItem.second) {
                    table[i][j] = table[i-1][j];
                } else {
                    table[i][j] = max(currItem.first + table[i-1][j-currItem.second], table[i-1][j]);
                }
            }
        }
        
        vector<int> indices;
        int row = items.size();
        int col = capacity;
        while(row != 0 && col != 0 ) {
            if(table[row][col] == table[row-1][col]) {
                row--;
            } else {
                indices.push_back(row-1);
                col -= items[row-1].second;
                row--;
            }
        }
        return indices;
        
    }
    
};


typedef long long int lli;

int main() {
    int items;
    vector<pair<int, int>> allItems;
    
    cin >> items;
    
    
    for (int i = 0; i < items; ++i) {
        int value;
        cin >> value;
        allItems.push_back(make_pair(value, value));
    }
    
    knapSack ksLower = knapSack();
    knapSack ksUpper = knapSack();
    vector<int> lowerRes = ksLower.knapsack(1000, allItems);
    
    
    int sumLower = 0;
    for (int i = 0; i < lowerRes.size(); ++i) {
        sumLower += allItems[lowerRes[i]].second;
    }
    
    int diff = 1000 - sumLower;
    
    if(diff == 0) {
        cout << sumLower << endl;
        return 0;
    }
    
    vector<int> upperRes = ksUpper.knapsack(1000+diff, allItems);
    
    
    int sumUpper = 0;
    for (int i = 0; i < upperRes.size(); ++i) {
        sumUpper += allItems[upperRes[i]].second;
    }
    cout << sumUpper << endl;
    return 0;
}

