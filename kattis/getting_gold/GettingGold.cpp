/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 19/2 - 18
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
#include <unordered_map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <climits>

using namespace std;

struct Graph{

    int width;
    int height;

    char board[50][50];
    bool visited[50][50];
};

class Dijkstras{

public:

    int shortestPath(Graph &graph, pair<int, int> &start) {
        int result = 0;
        queue<pair<int, int> > q;

        q.push(start);

        while(!q.empty()){
            pair<int, int> currNode = q.front();
            q.pop();

            int row = currNode.first;
            int col = currNode.second;

            if(graph.visited[row][col]) continue;
            graph.visited[row][col] = true;

            if (graph.board[row][col] == 'G') result++;

            bool riskFallInTrap = false;
            if (row - 1 >= 0            &&   graph.board[row-1][col] == 'T') riskFallInTrap = true;
            if (row + 1 < graph.height  &&   graph.board[row+1][col] == 'T') riskFallInTrap = true;
            if (col - 1 >= 0            &&   graph.board[row][col-1] == 'T') riskFallInTrap = true;
            if (col + 1 < graph.width   &&   graph.board[row][col+1] == 'T') riskFallInTrap = true;

            if(!riskFallInTrap){
                if (row - 1 >= 0            &&   graph.board[row-1][col] != '#') q.push(make_pair(row-1, col));
                if (row + 1 < graph.height  &&   graph.board[row+1][col] != '#') q.push(make_pair(row+1, col));
                if (col - 1 >= 0            &&   graph.board[row][col-1] != '#') q.push(make_pair(row, col-1));
                if (col + 1 < graph.width   &&   graph.board[row][col+1] != '#') q.push(make_pair(row, col+1));
            }
        }
        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);

    int width, height;
    cin >> width;
    cin >> height;

    char piece;
    pair<int, int> start;

    Graph graph = Graph();
    graph.width = width;
    graph.height = height;

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            cin >> piece;
            graph.board[row][col] = piece;
            graph.visited[row][col] = false;
            if(piece == 'P') start = make_pair(row, col);
        }
    }

    Dijkstras dijkstras = Dijkstras();
    int result = dijkstras.shortestPath(graph, start);
    cout << result << endl;

    return 0;
}