/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 22/1 -18
 *
 *  Comments: Union-Find data structure. Used when we want to check something is connected to another thing.
 *
 *  Lessons Learned: Need to work on analyze my solution and don't just test it in Kattis.
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

/**
 * Struct that contains the size of the nodes, needed to join the smaller subtree with the larger one.
 */
struct node {
    int size;
    node *parent;
};

// Global array consist of pointers to the nodes.
node *values[1000000];

/**
 * Find the root of given value, also do path compression, i.e skip some nodes on the way to root node.
 * If we have tree 1 -> 2 -> 3 (1 is root). Than we want that values[3] should point directly on 1 and not on 2.
 */
node* findRoot(int value) {
    while(values[value]->parent != nullptr){
        // Path compression
        values[value] = values[value]->parent;
    }
    return values[value];
}

/**
 * Function that will union element a and i. It will join element a to i if a is smaller than i, and vice versa.
 */
void unionCall(int a, int i) {
    node *rootA = findRoot(a);
    node *rootI = findRoot(i);

    // a and i is already union.
    if(rootA == rootI) return;

    // Join the smaller subset, with the larger one.
    if(rootA->size < rootI->size){
        rootA->parent = rootI;
        rootI->size += rootA->size;
        rootA->size = 0;
    }else{
        rootI->parent = rootA;
        rootA->size += rootI->size;
        rootI->size = 0;
    }
}

bool findCall(int a, int i) {
    return findRoot(i) == findRoot(a);
}

/**
 * Main function that will read the input and then go through all queries, either call unionCall or findCall.
 */
int main() {
    int n, q, a, b;
    char unionOrFind;
    scanf ("%d",&n);
    scanf ("%d",&q);

    // Fill the arrays with initial values.
    for (int j = 0; j < n; ++j) {
        node *root = new node;
        root->size = 1;
        root->parent = nullptr;
        values[j] = root;
    }

    // Go through all queries.
    for (int i = 0; i < q; ++i) {
        scanf(" %c", &unionOrFind);
        scanf ("%d",&a);
        scanf ("%d",&b);
        if(unionOrFind == '=') unionCall(a, b);
        else if(unionOrFind == '?') {
            bool same = findCall(a, b);
            if(same) printf("%s", "yes\n");
            else printf("%s", "no\n");
        }
    }
    return 0;
}