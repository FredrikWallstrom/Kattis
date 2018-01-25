/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date:
 *
 *  Comments:
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
typedef vector<long int> vi;

struct node{
    long int value;
    node *previous;
};

vi lis(vector<long> sequence) {
    vi lastElem;
    vector<vi > savedVectors;
    lastElem.push_back(sequence[0]);
    vi v;
    v.push_back(0);
    savedVectors.push_back(v);
    for (int i = 1; i < sequence.size(); ++i) {
        vi current;
        bool update = false;
        for (int j = 0; j < lastElem.size(); ++j) {
            if(sequence[i] <= lastElem[j]){
                lastElem[j] = sequence[i];
                vi l = savedVectors[j];
                l[l.size()-1] = i;
                savedVectors[j] = l;
                break;
            }else if(j == lastElem.size()-1){
                update = true;
                current = savedVectors[j];
            }
        }
        if(update){
            lastElem.push_back(sequence[i]);
            current.push_back(i);
            savedVectors.push_back(current);
        }
    }
    vi lis = savedVectors[savedVectors.size()-1];
    return lis;
}

int main() {
    int testCases;
    while(cin >> testCases){
        // Read the sequence.
        long int value;
        vi sequence;
        while(testCases--){
            cin >> value;
            sequence.push_back(value);
        }
        vi res = lis(sequence);
        cout << res.size() << endl;
        for (long re : res) cout << re << " ";
        cout << endl;
    }
    return 0;
}