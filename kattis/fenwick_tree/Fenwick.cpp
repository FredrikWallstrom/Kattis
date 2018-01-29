/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 22/1 -18
 *
 *  Comments: Union-Find data structure.
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
 * Global variable to store array.
 */
int a[];

/**
 * Increases a[i] with the number delta.
 */
void add(index i, number delta){
    while(i < n){
        a[i] += delta;
        index += i & -i;
    }
}

/**
 * A query for the values of a[0] + a[1] + ... + a[i-1].
 */
int number_sum(index end){
    int result = 0;
    while(end > 0){
        result += a[end];
        end -= end & -end;
    }
    return result;
}
/**
 * Main function that will read the input and then go through all queries, either call unionCall or findCall.
 */
int main() {
    int n, q, i, delta;
    char unionOrFind;
    scanf ("%d",&n);
    a[n];
    // Fill the arrays with initial values.
    for (int j = 0; j < n; ++j) a[j] == 0;

    scanf ("%d",&q);
    // Go through all queries.
    for (int i = 0; i < q; ++i) {
        scanf("%c", &ft);
        scanf ("%d",&i);
        if(ft == '+') {
            scanf ("%d",&delta);
            add(i, delta);
        }
        else if(ft == '?') {
            res = number_sum(i);
            printf("&d\n", res);
        }
    }
    return 0;
}