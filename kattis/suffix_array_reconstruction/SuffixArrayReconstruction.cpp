/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 5/3 - 18
 *
 *  Comments:
 *
 *  Lessons Learned:
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
    int nrOfTestCases;
    cin >> nrOfTestCases;

    while(nrOfTestCases--){
        int length, nrOfSuffixes;
        bool impossible = false;
        cin >> length >> nrOfSuffixes;
        int position;
        string suffix;
        string res(static_cast<unsigned long>(length), '0');

        while(nrOfSuffixes--) {
            cin >> position >> suffix;

            // Build the string as much as we can from the front to asterisk
            bool asterisk = false;
            auto currentResPosition = position - 1; // 0-indexing the string
            for (char i : suffix) {

                if (i == '*') {
                    asterisk = true;
                    break;
                }


                if (res[currentResPosition] != '0' && res[currentResPosition] != i) {
                    impossible = true;
                    break;
                } else {
                    res[currentResPosition] = i;
                }
                currentResPosition++;
            }

            // Build the string as much as we can from the back to asterisk
            if(asterisk){
                currentResPosition = static_cast<int>(res.size() - 1);
                for (auto i = static_cast<int>(suffix.size())-1; i >= 0; --i) {

                    if(suffix[i] == '*'){
                        break;
                    }

                    if(res[currentResPosition] != '0' && res[currentResPosition] != suffix[i]){
                        impossible = true;
                        break;
                    }else{
                        res[currentResPosition] = suffix[i];
                    }
                    currentResPosition--;
                }
            }
        }



        if(!impossible){
            for (char re : res) {
                if(re == '0'){
                    impossible = true;
                    break;
                }
            }
            if(impossible){
                cout << "IMPOSSIBLE" << endl;
            }else{
                cout << res << endl;
            }
        }else{
            cout << "IMPOSSIBLE" << endl;
        }
    }
    return 0;
}