/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 22/1 -18
 *
 *  Comments: Union-Find data structure.
 *
 *  Lessons Learned: Still need to work on, to think if my first solution is fast enough instead of just test it.
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

struct node {
    int size;
    int value;
};

node *values[1000000];

node findRoot(int value) {

    while(values[value]->value != value){
        // Path compression
        values[value] = values[values[value]->value];
        value = values[value]->value;
    }

    return *values[value];
}

void unionCall(int a, int i) {
    node rootA = findRoot(a);
    node rootI = findRoot(i);

    // a and i is already union.
    if(rootA.value == rootI.value) return;

    // Join the smaller subset, with the larger one.
    if(rootA.size < rootI.size){
        values[rootI.value] = values[rootA.value];
        rootI.size += rootA.size;
        rootA.size = 0;
    }else{
        values[rootA.value] = values[rootI.value];
        rootA.size += rootI.size;
        rootI.size = 0;
    }
}

bool findCall(int a, int i) {
    return findRoot(i).value == findRoot(a).value;

}

int main() {

    int n, q, a, b;
    char unionOrFind;
    cin >> n >> q;

    // Fill the arrays with initial values.
    for (int j = 0; j < n; ++j) {
        auto *root = new node;
        root->size = 0;
        root->value = j;
        values[j] = root;
    }

    // Go through all queries.
    for (int i = 0; i < q; ++i) {
        cin >> unionOrFind;
        cin >> a >> b;
        if(unionOrFind == '=') unionCall(a, b);
        else if(unionOrFind == '?') {
            bool same = findCall(a, b);
            if(same) cout << "yes" << endl;
            else cout << "no" << endl;
        }
    }
    return 0;
}