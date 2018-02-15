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

struct Edge{
    int startTime, step, cost;
};

struct Node{
    int id;
    bool visited = false;
    vector<pair<Edge, Node*> > neighbours;
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

    void addEdge(int &fromIndex, int &toIndex, int &startTime, int &step, int &cost){
        Node *fromNode = &nodes.at(fromIndex);
        Node *toNode = &nodes.at(toIndex);
        Edge edge = Edge();
        edge.startTime = startTime;
        edge.step = step;
        edge.cost = cost;
        fromNode->neighbours.emplace_back(edge, toNode);
    };

    int calculateCostToNeighbour(int &distCurrNode, Edge &edge){
        if(edge.step == 0){
            if(edge.startTime >= distCurrNode) return (edge.startTime - distCurrNode) + edge.cost;
            else return -1;
        }

        int time = edge.startTime;
        while(true){
            if(time >= distCurrNode) return (time - distCurrNode) + edge.cost;
            time += edge.step;
        }
    };
};

class Dijkstras{

public:

    pair<dataStructure, dataStructure> shortestPath(Graph &graph, int &startIndex) {
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

            for(int i = 0; i < currNode->neighbours.size(); ++i){
                pair<Edge, Node*> neighbour = currNode->neighbours[i];

                if(neighbour.second->visited) continue;

                int w = graph.calculateCostToNeighbour(distance[currNode->id], neighbour.first);
                if(w == -1) continue;

                if(distance[neighbour.second->id] > distance[currNode->id] + w){
                    distance[neighbour.second->id] = distance[currNode->id] + w;
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
    int nrNodes, nrEdges, nrQueries, startNode;
    int fromNode, toNode, startTime, step, cost;
    int query;

    scanf("%d%d%d%d", &nrNodes, &nrEdges, &nrQueries, &startNode);

    while(nrNodes != 0 || nrEdges != 0 || nrQueries != 0 || startNode != 0){
        Dijkstras dijkstras = Dijkstras();
        Graph graph = Graph();

        while(nrEdges--){
            scanf("%d%d%d%d%d", &fromNode, &toNode, &startTime, &step, &cost);
            graph.addNode(fromNode);
            graph.addNode(toNode);
            graph.addEdge(fromNode, toNode, startTime, step, cost);
        }

        pair<dataStructure, dataStructure> result = dijkstras.shortestPath(graph, startNode);

        dataStructure distanceMap = result.first;
        dataStructure prevMap = result.second;

        while(nrQueries--){
            scanf("%d", &query);
            if(distanceMap.count(query) && distanceMap[query] != INT_MAX) printf("%d\n", distanceMap[query]);
            else printf("%s\n", "Impossible");
        }

        printf("\n");
        scanf("%d%d%d%d", &nrNodes, &nrEdges, &nrQueries, &startNode);
    }
    return 0;
}