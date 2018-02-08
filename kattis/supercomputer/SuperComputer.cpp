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

int main() {
    ios::sync_with_stdio(false);
    long long int n, k, i, l, r;
    char ft;

    cin >> n;
    cin >> k;

    FenwickTree FT = FenwickTree(vector<long long int>(n));

    while(k > 0){
        cin >> ft;

        if(ft=='F'){
            cin >> i;
            long long int currentBit = FT.sum(i) - FT.sum(i-1);
            if(currentBit == 0){
                FT.add(i-1, 1);
            }else{
                FT.add(i-1, -1);
            }
        }else{
            cin >> l;
            cin >> r;
            long long int range = FT.sum(r) - FT.sum(l-1);
            cout << range << endl;
        }
        k--;
    }
    return 0;
}