/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 4/2 - 18
 *
 *  Comments: A little bit tricky to understand the problem.
 *              We got a list with numbers that can be turned with nothing happens, like:
 *              1, 2, 5, 6, 8, 9, 10, 11, 12, 15, 16, 18... and so on.
 *              The input is index in this list.
 *              So if the input is 7, the number we want is 10
 *              Than we also wan to flip 10 and print it backwards, since the clock is upside down.
 *              So we want to print 01.
 *              For input 11, we have number 16. And we want to print 91. And so on...
 *              To do this we can turn the input to base-7 number and than flip the 6 to a 9 and vice versa.
 *
 *  Lessons Learned:
 */

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

using namespace std;
typedef vector<int> vi;

// Numbers we can turn:
// 0 = 0
// 1 = 1
// 2 = 2
// 5 = 5
// 6 = 9
// 8 = 8
// 9 = 6

int main() {
    int k;
    while(cin >> k){

        // Convert to base 7.
        // The remainder is the answer of the base-7 conversion backwards, so we just need to print it directly.
        // EX:
        // 98 would give remainder 0,
        // Than k = k / 7 = 14
        // 14 would give remainder 0,
        // k = k / 7 = 2
        // 2 would give remainder 2,
        // So the answer printed is 002 and 98 in base 7 is 200
        int remainder = k%7;
        k = k / 7;

        // According to input,
        // 3 corresponds to a 5.
        // 4 corresponds to a 9.
        // 5 corresponds to a 8.
        if(remainder == 0) cout << 0;
        else if(remainder == 1) cout << 1;
        else if(remainder == 2) cout << 2;
        else if(remainder == 3) cout << 5;
        else if(remainder == 4) cout << 9;
        else if(remainder == 5) cout << 8;
        else if(remainder == 6) cout << 6;

        // We are finish when k == 0.
        while(k > 0){
            remainder = k%7;
            k = k / 7;
            if(remainder == 0) cout << 0;
            else if(remainder == 1) cout << 1;
            else if(remainder == 2) cout << 2;
            else if(remainder == 3) cout << 5;
            else if(remainder == 4) cout << 9;
            else if(remainder == 5) cout << 8;
            else if(remainder == 6) cout << 6;
        }
        cout << endl;
    }
    return 0;
}