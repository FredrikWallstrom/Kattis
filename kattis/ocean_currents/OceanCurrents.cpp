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
typedef vector<long long int> dataStructure;

struct Node{
    long long int id;
    bool visited = false;
    vector<pair<long long int, Node*> > neighbours;
};

struct Graph{
    vector<Node> nodes;

    void addNode(long long int &node){
        Node n = Node();
        n.id = node;
        nodes.push_back(n);
    }

    void addEdge(long long int &fromIndex, long long int &toIndex, long long int cost){
        Node *fromNode = &nodes[fromIndex];
        Node *toNode = &nodes[toIndex];
        fromNode->neighbours.emplace_back(cost, toNode);
    }
};

class Dijkstras{

public:

    dataStructure shortestPath(Graph &graph, long long int &startIndex, long long int &endIndex) {
        dataStructure distance(graph.nodes.size(), INT_MAX);
        priority_queue< pair<long long int, long long int>, vector<pair<long long int, long long int> >, greater<pair<long long int, long long int> > > pq;

        for (auto &node : graph.nodes) {
            node.visited = false;
        }

        distance[startIndex] = 0;
        pq.push(make_pair(distance[startIndex], startIndex));

        while(!pq.empty()){
            long long int currNodeIndex = pq.top().second;
            pq.pop();

            Node *currNode = &graph.nodes[currNodeIndex];
            currNode->visited = true;

            if(currNode->id == endIndex) break;

            for(long long int i = 0; i < currNode->neighbours.size(); ++i){
                pair<long long int, Node*> neighbour = currNode->neighbours[i];

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

int main() {
    ios_base::sync_with_stdio(false);

    long long int nrOfRows, nrOfCols;
    vector<pair<long long int, long long int> > directions;
    directions.push_back(make_pair(-1, 0));
    directions.push_back(make_pair(-1, 1));
    directions.push_back(make_pair(0, 1));
    directions.push_back(make_pair(1, 1));
    directions.push_back(make_pair(1, 0));
    directions.push_back(make_pair(1, -1));
    directions.push_back(make_pair(0, -1));
    directions.push_back(make_pair(-1, -1));


    Graph graph = Graph();
    scanf("%lld%lld", &nrOfRows, &nrOfCols);
    long long int sea[nrOfRows][nrOfCols];
    long long int nodeMap[nrOfRows][nrOfCols];

    long long int count = 0;
    for (long long int i = 0; i < nrOfRows; ++i) {

        for (long long int j = 0; j < nrOfCols; ++j) {
            char c;
            scanf(" %c", &c);

            int value = c - '0';
            sea[i][j] = value;
            nodeMap[i][j] = count;
            graph.addNode(count);
            count++;
        }
    }

    for (long long int k = 0; k < nrOfRows; ++k) {
        for (long long int i = 0; i < nrOfCols; ++i) {
            for (long long int j = 0; j < directions.size(); ++j) {
                long long int row = k + directions[j].first;
                long long int col = i + directions[j].second;
                if(row >= 0 && col >= 0 && row < nrOfRows && col < nrOfCols){
                    long long int v = sea[k][i];
                    if(v == j) graph.addEdge(nodeMap[k][i], nodeMap[row][col], 0);
                    else graph.addEdge(nodeMap[k][i], nodeMap[row][col], 1);
                }
            }
        }
    }

    Dijkstras dijkstras = Dijkstras();
    long long int queries;
    scanf("%lld", &queries);

    for (long long int l = 0; l < queries; ++l) {
        long long int rs, cs, rd, cd;
        scanf("%lld%lld%lld%lld", &rs, &cs, &rd, &cd);
        dataStructure result = dijkstras.shortestPath(graph, nodeMap[rs-1][cs-1], nodeMap[rd-1][cd-1]);
        printf("%lld\n", result[nodeMap[rd-1][cd-1]]);
    }

    return 0;
}