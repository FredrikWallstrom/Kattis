/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 29/1 -18
 *
 *  Comments: Fenwick tree. Will be used when we want to sum something in a list etc. range sum also.
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



class FenwickTree{

private:
    vector<long long int> tree;

public:

    /**
     * Constructor to create an instance.
     */
    explicit FenwickTree(vector<long long int> vector) {
        tree.resize(vector.size() + 1, 0);
        buildTree(vector);
    };

    /**
     * Initialize the tree.
     */
    void buildTree(vector<long long int> &vector) {
        for (long long int i = 1; i <= vector.size(); ++i) {
            add(i - 1, vector[i - 1]);
        }
    }

    /**
    * Increases a[i] with the number delta.
    * Go forward in the bitTree and change all the values with delta.
    * The last syntax is to add the last set bit
    */
    void add(long long int i, long long int delta){
        i++;
        while(i <= tree.size()){
            tree[i] += delta;
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
            result += tree[end];
            end -= end & -end;
        }
        return result;
    }
};

/**
 * Main function that will read the input and then go through all queries, either call sum or add.
 */
int main() {
    ios::sync_with_stdio(false);
    long long int i, delta, n, q;
    char ft;

    scanf("%lld", &n);
    scanf("%lld", &q);

    FenwickTree FT = FenwickTree(vector<long long int>(n));

    while(q > 0){
        scanf(" %c", &ft);
        scanf("%lld", &i);
        if(ft=='+'){
            scanf("%lld", &delta);
            FT.add(i, delta);
        }else{
            long long int res = FT.number_sum(i);
            printf("%lld\n", res);
        }
        q--;
    }
    return 0;
}