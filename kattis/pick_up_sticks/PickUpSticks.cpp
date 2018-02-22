/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date:
 *
 *  Comments: 22/2 - 18
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

void explore(int curr, vi &visited, map<int, vi> &sticks, stack<int> &res){
    // We are visiting current node for the moment.
    visited[curr] = 1;
    for (int i = 0; i < sticks[curr].size(); ++i) {
            // Already visited.
        if(visited[sticks[curr][i]] == 2) continue;
            // Impossible, cycle detected.
        else if(visited[sticks[curr][i]] == 1) return;
            // Keep explore.
        else explore(sticks[curr][i], visited, sticks, res);
    }
    res.push(curr);
    visited[curr] = 2;
}

int main() {
    int nrSticks, nrLines;
    int a, b;

    scanf("%d%d", &nrSticks, &nrLines);
    map<int, vi> sticks;
    vi visited(static_cast<unsigned long>(nrSticks + 1), 0);
    stack<int> res;

    for (int k = 1; k <= nrLines; ++k) scanf("%d%d", &a, &b), sticks[a].push_back(b);

    for (int i = 1; i <= nrSticks; ++i) {
        if(visited[i] == 0) explore(i, visited, sticks, res);
        else if(visited[i] == 1) {
            printf("IMPOSSIBLE");
            return 0;
        }
    }

    auto loopSize = static_cast<int>(res.size());
    for (int i = 0; i < loopSize; ++i) {
        printf("%d\n", res.top());
        res.pop();
    }

    return 0;
}