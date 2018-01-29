/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 29/1 -18
 *
 *  Comments: Fenwick tree solution. Create fenwickTree with only 1:s. Save the indexes for the incoming values
 *            and iterate over them, for every index subtract one from the fenwickTree and than take the range_sum.
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

int n;
int fenwickTree[100001];

/**
 * Increases a[i] with the number delta.
 * Go forward in the bitTree and change all the values with delta.
 * The last syntax is to add the last set bit
 */
void add(int i, int delta){
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
int number_sum(int end){
    int result = 0;
    while(end > 0){
        result += fenwickTree[end];
        end -= end & -end;
    }
    return result;
}

int range_sum(int from, int to)
{
    return number_sum(to) - number_sum(from-1);
}

int main() {

    int number;
    scanf("%d", &n);
    vi numbers(n+1);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &number);
        // Initialize the fenwickTree with 1:s.
        add(i, 1);
        // Store the indexes of the numbers. So When we iterate over numbers,
        // we know we got value one first, last value at the end and so on.
        numbers[number] = i;
    }

    int start = 1;
    int end = n;

    for (int j = 1; j <= n; ++j) {
        if(j%2 == 0){
            // Even.
            // Take the last value and go closer to middle.
            // For every taken value we subtract one in the fenwickTree,
            // Which mean we can do range_sum between current and end.
            add(numbers[end], -1);
            int res = range_sum(numbers[end], n);
            cout << res << endl;
            end--;
        }else{
            // ODD.
            // Take the first value and go closer to middle.
            // For every taken value we subtract one in the fenwickTree,
            // Which mean we can do range_sum between start and current value.
            add(numbers[start], -1);
            int res = range_sum(1, numbers[start]);
            cout << res << endl;
            start++;
        }
    }
    return 0;
}