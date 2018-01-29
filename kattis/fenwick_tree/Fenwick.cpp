/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 29/1 -18
 *
 *  Comments: Fenwick tree.
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

long long n,q;
char ft;
long long fenwickTree[5000001] ,delta;

/**
 * Increases a[i] with the number delta.
 * Go forward in the bitTree and change all the values with delta.
 * The last syntax is to add the last set bit
 */
void add(long long int i, long long int delta){
    // Add on i+1 since we want to increment the value on position i not on index i.
    i++;
    while(i <= n){
        fenwickTree[i] += delta;
        i += i & -i;
    }
}

/**
 * A query for the values of a[0] + a[1] + ... + a[i-1].
 * Go through backward in the bitTree and check sum all values at the way down.
 * The last syntax is to remove the last set bit
 */
long long int number_sum(long long end){
    long long int result = 0;
    while(end > 0){
        result += fenwickTree[end];
        end -= end & -end;
    }
    return result;
}

/**
 * Main function that will read the input and then go through all queries, either call sum or add.
 */
int main() {
    ios::sync_with_stdio(false);
    long long int i;

    scanf("%lld", &n);
    scanf("%lld", &q);
    
    while(q > 0){
        scanf(" %c", &ft);
        scanf("%lld", &i);
        if(ft=='+'){
            scanf("%lld", &delta);
            add(i, delta);
        }else{
            long long int res = number_sum(i);
            printf("%lld\n", res);
        }
        q--;
    }
    return 0;
}