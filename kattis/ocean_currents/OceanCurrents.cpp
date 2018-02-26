/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 12/2 - 18
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
typedef map<int, int> dataStructure;

struct Node{
    int id;
    bool visited = false;
    vector<pair<int, Node*> > neighbours;
};

struct Graph{
    map<int, Node> nodes;

    void addNode(int &node){
        if(!nodes.count(node)){
            Node n = Node();
            n.id = node;
            nodes[node] = n;
        }
    }

    void addEdge(int &fromIndex, int &toIndex, int cost){
        Node *fromNode = &nodes.at(fromIndex);
        Node *toNode = &nodes.at(toIndex);
        fromNode->neighbours.emplace_back(cost, toNode);
    };
};

class Dijkstras{

public:

    pair<dataStructure, dataStructure> shortestPath(Graph &graph, int &startIndex, int &endIndex) {
        dataStructure distance;
        dataStructure prev;
        priority_queue< pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

        for (auto &node : graph.nodes) {
            node.second.visited = false;
            distance[node.second.id] = INT_MAX;
            prev[node.second.id] = -1;
        }

        distance[startIndex] = 0;
        prev[startIndex] = startIndex;
        pq.push(make_pair(distance[startIndex], startIndex));

        while(!pq.empty()){
            int currNodeIndex = pq.top().second;
            pq.pop();

            Node *currNode = &graph.nodes[currNodeIndex];
            currNode->visited = true;

            if(currNode->id == endIndex) break;

            for(int i = 0; i < currNode->neighbours.size(); ++i){
                pair<int, Node*> neighbour = currNode->neighbours[i];

                if(neighbour.second->visited) continue;

                if(distance[neighbour.second->id] > distance[currNode->id] + neighbour.first){
                    distance[neighbour.second->id] = distance[currNode->id] + neighbour.first;
                    prev[neighbour.second->id] = currNode->id;
                    pq.push(make_pair(distance[neighbour.second->id], neighbour.second->id));
                }
            }
        }
        return make_pair(distance, prev);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    
    int nrOfRows, nrOfCols;
    vector<pair<int, int> > directions;
    directions.push_back(make_pair(-1, 0));
    directions.push_back(make_pair(-1, 1));
    directions.push_back(make_pair(0, 1));
    directions.push_back(make_pair(1, 1));
    directions.push_back(make_pair(1, 0));
    directions.push_back(make_pair(1, -1));
    directions.push_back(make_pair(0, -1));
    directions.push_back(make_pair(-1, -1));

    scanf("%d%d", &nrOfRows, &nrOfCols);
    int sea[nrOfRows][nrOfCols];
    int nodeMap[nrOfRows][nrOfCols];
    Graph graph = Graph();


    int count = 0;
    for (int i = 0; i < nrOfRows; ++i) {
        for (int j = 0; j < nrOfCols; ++j) {
            int n;
            scanf("%d", &n);
            sea[i][j] = n;
            nodeMap[i][j] = count;
            graph.addNode(count);
            count++;
        }
    }

    for (int k = 0; k < nrOfRows; ++k) {
        for (int i = 0; i < nrOfCols; ++i) {
            for (int j = 0; j < directions.size(); ++j) {
                int row = i + directions[j].first;
                int col = i + directions[j].second;
                if(row >= 0 && col >= 0 && row < nrOfRows && col < nrOfCols){
                    int v = sea[i][j];
                    if(v == j) graph.addEdge(nodeMap[i][j], nodeMap[row][col], 0);
                    else graph.addEdge(nodeMap[i][j], nodeMap[row][col], 1);
                }
            }
        }
    }

    Dijkstras dijkstras = Dijkstras();

    int queries;
    scanf("%d", &queries);

    for (int l = 0; l < queries; ++l) {
        int rs, cs, rd, cd;
        scanf("%d%d%d%d", &rs, &cs, &rd, &cd);
        pair<dataStructure, dataStructure> result = dijkstras.shortestPath(graph, nodeMap[rs][cs], nodeMap[rd][cd]);
        dataStructure distanceMap = result.first;
        printf("%d\n", distanceMap[nodeMap[rd][cd]]);
    }

    return 0;
}