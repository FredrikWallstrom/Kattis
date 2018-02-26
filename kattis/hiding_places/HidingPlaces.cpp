/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 26/2 - 18
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
typedef vector<int> dataStructure;

struct Node{
    int id;
    bool visited = false;
    vector<pair<int, Node*> > neighbours;
};

struct Graph{
    vector<Node> nodes;

    void addNode(int &node){
        Node n = Node();
        n.id = node;
        nodes.push_back(n);
    }

    void addEdge(int &fromIndex, int &toIndex, int cost){
        Node *fromNode = &nodes[fromIndex];
        Node *toNode = &nodes[toIndex];
        fromNode->neighbours.emplace_back(cost, toNode);
    };
};

class Dijkstras{

public:

     dataStructure shortestPath(Graph &graph, int &startIndex) {
        dataStructure distance(graph.nodes.size(), INT_MAX);
        priority_queue< pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

        for (auto &node : graph.nodes) {
            node.visited = false;
        }

        distance[startIndex] = 0;
        pq.push(make_pair(distance[startIndex], startIndex));

        while(!pq.empty()){
            int currNodeIndex = pq.top().second;
            pq.pop();

            Node *currNode = &graph.nodes[currNodeIndex];
            currNode->visited = true;

            for(int i = 0; i < currNode->neighbours.size(); ++i){
                pair<int, Node*> neighbour = currNode->neighbours[i];

                if(neighbour.second->visited) continue;

                if(distance[neighbour.second->id] > distance[currNode->id] + neighbour.first){
                    distance[neighbour.second->id] = distance[currNode->id] + neighbour.first;
                    pq.push(make_pair(distance[neighbour.second->id], neighbour.second->id));
                }
            }
        }
        return distance;
    }
};

int convertChar(char &c){
    if(c == 'a') return 0;
    if(c == 'b') return 1;
    if(c == 'c') return 2;
    if(c == 'd') return 3;
    if(c == 'e') return 4;
    if(c == 'f') return 5;
    if(c == 'g') return 6;
    if(c == 'h') return 7;
}

char convertInt(int &c){
    if(c == 0) return 'a';
    if(c == 1) return 'b';
    if(c == 2) return 'c';
    if(c == 3) return 'd';
    if(c == 4) return 'e';
    if(c == 5) return 'f';
    if(c == 6) return 'g';
    if(c == 7) return 'h';
}

int main() {
    ios_base::sync_with_stdio(false);
    int testCases;
    int board[8][8];
    int nodeMap[8][8];
    int count = 0;
    Graph graph = Graph();

    scanf("%d", &testCases);

    // Build graph
    vector<pair<int, int> > directions;
    directions.push_back(make_pair(-2, -1));
    directions.push_back(make_pair(-2, 1));
    directions.push_back(make_pair(-1, 2));
    directions.push_back(make_pair(1, 2));
    directions.push_back(make_pair(2, 1));
    directions.push_back(make_pair(2, -1));
    directions.push_back(make_pair(-1, -2));
    directions.push_back(make_pair(1, -2));

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            nodeMap[i][j] = count;
            graph.addNode(count);
            count++;
        }
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            for (int k = 0; k < directions.size(); ++k) {
                int row = i + directions[k].first;
                int col = j + directions[k].second;
                if(row >= 0 && col >= 0 && row < 8 && col < 8){
                    graph.addEdge(nodeMap[i][j], nodeMap[row][col], 1);
                }
            }
        }
    }


    while(testCases--){

        char c;
        int row;
        scanf(" %c", &c);
        scanf("%d", &row);
        int col = convertChar(c);

        Dijkstras dijkstras = Dijkstras();
        dataStructure result = dijkstras.shortestPath(graph, nodeMap[row-1][col]);

        int maxx = 0;
        vector<pair<int,int> > res;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if(result[nodeMap[i][j]] > maxx){
                    maxx = result[nodeMap[i][j]];
                }
            }
        }
        printf("%d ", maxx);

        for (int i = 7; i >= 0; --i) {
            for (int j = 0; j < 8; ++j) {
                if(result[nodeMap[i][j]] == maxx){
                    printf("%c%d ", convertInt(j), i+1);
                }
            }
        }
        printf("\n");
    }
    return 0;
}