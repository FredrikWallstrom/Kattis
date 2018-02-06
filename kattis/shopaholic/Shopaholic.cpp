#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    long long int items, value;
    cin >> items;
    vector<long long int> allItems;
    
    for (long long int i = 0; i < items; ++i) {
        cin >> value;
        allItems.push_back(value);
    }
    
    sort(allItems.begin(), allItems.end(), greater<long long int>());
    
    long long int index = 2;
    long long int res = 0;
    while(index <= allItems.size() - 1){
        res += allItems[index];
        index += 3;
    }
    cout << res << endl;
    
    return 0;
}
