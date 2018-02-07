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
#include <stack>

using namespace std;

int main() {
    string input = "";
    
    while (true){
        cin >> input;
        if(input == "END"){
            return 0;
        }
        
        double asInt = stod(input);
        
        if(asInt == 1 || asInt == 0) {
            cout << "MEMBER" << endl;
            continue;
        }
      
        long double value = stod(input);
        bool isMember = true;
        for (int i = 0; i < 20; i++) {
            value = value * 3;
            long double integerPartDouble;
            value = modf(value, &integerPartDouble);
            int integerPart = static_cast<int>(integerPartDouble);
            if(integerPart == 1){
                cout << "NON-MEMBER" << endl;
                isMember = false;
                break;
            }
        } 
        if(isMember) cout << "MEMBER" << endl; 
    }
    return 0;
}

