/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 15/2 - 18
 *
 *  Comments: Dijkstras with time intervals.
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
    int fromNode, toNode;
    int closed, cost;
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

    void addEdge(int &fromIndex, int &toIndex, int &cost){
        Node *fromNode = &nodes.at(fromIndex);
        Node *toNode = &nodes.at(toIndex);
        Edge edge = Edge();
        edge.fromNode = fromIndex;
        edge.toNode = toIndex;
        edge.cost = cost;
        edge.closed = -1;
        fromNode->neighbours.emplace_back(edge, toNode);
    };

    int calculateCostToNeighbour(int &distCurrNode, Edge &edge, int &startingTimeDiff){
        if(edge.closed == -1) return edge.cost;
        if(distCurrNode + startingTimeDiff < edge.closed) return edge.cost;
        if(distCurrNode + startingTimeDiff >= edge.closed + edge.cost) return edge.cost;
        else return ((edge.closed + edge.cost) - (distCurrNode + startingTimeDiff)) + edge.cost;
    };
};

class Dijkstras{

public:

    dataStructure shortestPath(Graph &graph, int &startIndex, int &startingTimeDiff) {
        dataStructure distance;
        priority_queue< pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

        for (auto &node : graph.nodes) {
            node.second.visited = false;
            distance[node.second.id] = INT_MAX;
        }

        distance[startIndex] = 0;
        pq.push(make_pair(distance[startIndex], startIndex));

        while(!pq.empty()){
            int currNodeIndex = pq.top().second;
            pq.pop();

            Node *currNode = &graph.nodes[currNodeIndex];
            currNode->visited = true;

            for(int i = 0; i < currNode->neighbours.size(); ++i){
                pair<Edge, Node*> neighbour = currNode->neighbours[i];

                if(neighbour.second->visited) continue;

                int w = graph.calculateCostToNeighbour(distance[currNode->id], neighbour.first, startingTimeDiff);

                if(distance[neighbour.second->id] > distance[currNode->id] + w){
                    distance[neighbour.second->id] = distance[currNode->id] + w;
                    pq.push(make_pair(distance[neighbour.second->id], neighbour.second->id));
                }
            }
        }
        return distance;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int nrIntersections, nrStreets;
    int lukaStart, lukaGoal, startingTimeDiff, georgeIntersections;

    scanf("%d%d", &nrIntersections, &nrStreets);
    scanf("%d%d%d%d", &lukaStart, &lukaGoal, &startingTimeDiff, &georgeIntersections);

    vector<int> georgeRoute;
    int intersection;
    while(georgeIntersections--){
        scanf("%d", &intersection);
        georgeRoute.push_back(intersection);
    }


    Dijkstras dijkstras = Dijkstras();
    Graph graph = Graph();

    int fromNode, toNode, cost;
    while(nrStreets--){
        scanf("%d%d%d", &fromNode, &toNode, &cost);
        graph.addNode(fromNode);
        graph.addNode(toNode);
        graph.addEdge(fromNode, toNode, cost);
        graph.addEdge(toNode, fromNode, cost);
    }

    int currentTimeGeorge = 0;
    for (int i = 0; i < georgeRoute.size(); ++i) {
        if(i+1 == georgeRoute.size()) continue;

        bool first = true;

        for (int j = 0; j < graph.nodes.size(); ++j) {
            for (int k = 0; k < graph.nodes[j].neighbours.size(); ++k) {
                if((graph.nodes[j].neighbours[k].first.fromNode == georgeRoute[i] &&
                        graph.nodes[j].neighbours[k].first.toNode == georgeRoute[i+1]) ||
                        (graph.nodes[j].neighbours[k].first.fromNode == georgeRoute[i+1] &&
                        graph.nodes[j].neighbours[k].first.toNode == georgeRoute[i])){

                    graph.nodes[j].neighbours[k].first.closed = currentTimeGeorge;

                    if(first) first = false;
                    else currentTimeGeorge += graph.nodes[j].neighbours[k].first.cost;
                }
            }
        }
    }
    dataStructure result = dijkstras.shortestPath(graph, lukaStart, startingTimeDiff);
    printf("%d\n", result[lukaGoal]);
    return 0;
}