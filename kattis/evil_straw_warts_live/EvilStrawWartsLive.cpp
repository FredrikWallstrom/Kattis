/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date:
 *
 *  Comments: 5/3 - 18
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
#include <unordered_map>

using namespace std;

bool isPalindrome(string &text){
    unordered_map<char, int> count;

    for (char i : text) {
        count[i]++;
    }

    int odd = 0;
    for (int i = 0; i < count.size(); ++i) {
        if((count[i] % 2) != 0){
            odd++;
        }

        if(odd > 1){
            break;
        }
    }
    return odd <= 1;

}

int doSwap(string &text, int from, int to){
    int swaps = 0;

    if(from < to){
        while(from != to){
            char tmp = text[from];
            text[from] = text[from+1];
            text[from+1] = tmp;
            from++;
            swaps++;
        }
    }else{
        while(from != to){
            char tmp = text[from];
            text[from] = text[from-1];
            text[from-1] = tmp;
            from--;
            swaps++;
        }
    }
    return swaps;
}

int doSwaps(string &text){
    int swaps = 0;

    int start = 0;
    auto end = static_cast<int>(text.size()-1);

    int tmpStart = start;
    int tmpEnd = end;
    while(start < end){

        if(text[start] == text[tmpEnd]){
            swaps += doSwap(text, tmpEnd, end);
            start++;
            end--;
            tmpEnd = end;
            tmpStart = start;
        }else{
            tmpEnd--;
        }

        if(text[tmpStart] == text[end]){
            swaps += doSwap(text, tmpStart, start);
            start++;
            end--;
            tmpEnd = end;
            tmpStart = start;
        }else{
            tmpStart++;
        }
    }
    return swaps;
}

int main() {
    int nrOfTestCases;
    cin >> nrOfTestCases;

    while(nrOfTestCases--) {
        string text;
        cin >> text;

        if (isPalindrome(text)) {
            int swaps = doSwaps(text);
            cout << swaps << endl;
        }else{
            cout << "Impossible" << endl;
        }
    }

    return 0;
}