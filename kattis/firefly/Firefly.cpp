#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <map>
#include <set>
#include <queue>

using namespace std;

struct FenwickTree {
    
private:
    vector<long long int> tree;
public:
    FenwickTree(vector<long long int> array) {
        tree.resize(array.size() + 1, 0);
        buildFWTree(array);
    };
    
    void buildFWTree(vector<long long int> &array) {
        for(long long int i = 1; i <= array.size(); ++i) {
            add(i-1, array[i-1]);
        }
    }
    
    void add(long long int index, long long int delta) {
        index = index + 1;
        while (index < tree.size()) {
            tree[index] += delta;
            index += index & (-index);
        }
    }
    
    long long int sum(long long int end) {
        long long int res = 0;
        long long int index = end;
        while (index > 0) {
            res += tree[index];
            index -= index & (-index);
        }
        
        return res;
    }
    
    
};

typedef long long int lli;

int main() {
    lli numberOfObstacles, levels;
    scanf("%lld %lld", &numberOfObstacles, &levels);
    
    FenwickTree upper = FenwickTree(vector<lli>(levels));
    FenwickTree lower = FenwickTree(vector<lli>(levels));
    
    bool even = true;
    lli value;
    for (lli i = 1; i <= numberOfObstacles; ++i) {
        scanf("%lld", &value);
        if(even) {
            lower.add(value, 1);
        } else {
            upper.add(value, 1);
        }
        even = !even;
    }
    
    lli minCollisions = numberOfObstacles + 10;
    lli bestLevelCount = 0;
    for (lli i = 1; i<= levels; ++i) {
        //calculate nr of all obstacles larger than our current level
        lli tmpCollisionsLower = lower.sum(levels)-lower.sum(i);
        //calculate nr of all obstacles that are long enough to reach us on our level
        //here we calculate the sum from "index to end of array" and we choose index such that currLevel gives us maxlevel - currlevel in the array.
        // the plus one in tmpCollisionsUpper is a fix with indexes.
        lli tmpCollisionsUpper = upper.sum(levels)- upper.sum(levels-i+1);
        lli totalCollisions = tmpCollisionsLower + tmpCollisionsUpper;
        if(totalCollisions < minCollisions) {
            minCollisions = totalCollisions;
            bestLevelCount = 1;
        } else if(totalCollisions == minCollisions) {
            bestLevelCount++;
        }
    }
    
    printf("%lld %lld", minCollisions, bestLevelCount);
    
    // för dom undre. låt varje höjd representera en plats i fenwickträded. så index 1 är alla med höjd 1.
    //[0,1,0,1,0,1,0,0]
    //för dom övre, eget fenwickträd fast vi summerar som vanligt.
   // [0,1,0,1,0,1,0,0]
    return 0;
}
