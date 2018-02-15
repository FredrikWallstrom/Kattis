/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 15/2 - 18
 *
 *  Comments: Changed from nodes to edges.
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
typedef unordered_map<int, int> dataStructure;

struct Edge{
    int source, destination, cost;
};

struct Graph{
    int nrNodes{}, nrEdges{};
    vector<Edge> edges;

    void addEdge(int &source, int &destination, int &cost){
        Edge edge = Edge();
        edge.source = source;
        edge.destination = destination;
        edge.cost = cost;
        edges.push_back(edge);
    };
};

class Bellman{

public:

    pair<dataStructure, dataStructure> shortestPath(Graph &graph, int &startIndex) {
        dataStructure distance;
        dataStructure prev;

        // Set all edges cost to infinity.
        for (int i = 0; i < graph.nrNodes; ++i) {
            distance[i] = INT_MAX;
            prev[i] = -1;
        }
        distance[startIndex] = 0;

        // Relaxation to find the shortest path.
        for (int node = 0; node < graph.nrNodes - 1; ++node)
        {
            for (int edge = 0; edge < graph.nrEdges; ++edge)
            {
                int fromNode = graph.edges[edge].source;
                int toNode = graph.edges[edge].destination;
                int cost = graph.edges[edge].cost;
                if (distance[fromNode] != INT_MAX && (distance[fromNode] + cost < distance[toNode])){
                    distance[toNode] = distance[fromNode] + cost;
                    prev[toNode] = fromNode;
                }
            }
        }

        // Check for negative cycles.
        for (int node = 0; node < graph.nrNodes - 1; ++node)
        {
            for (int edge = 0; edge < graph.nrEdges; ++edge)
            {
                int fromNode = graph.edges[edge].source;
                int toNode = graph.edges[edge].destination;
                int cost = graph.edges[edge].cost;

                if(distance[fromNode] == INT_MIN){
                    // Nodes connected to fromNode and fromNode is in negative cycle, toNode is also in negative cycle.
                    distance[toNode] = INT_MIN;
                    prev[toNode] = INT_MIN;
                }
                else if (distance[fromNode] != INT_MAX && (distance[fromNode] + cost < distance[toNode])) {
                    // There is a negative loop.
                    distance[toNode] = INT_MIN;
                    prev[toNode] = INT_MIN;
                }
            }
        }
        return make_pair(distance, prev);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int nrNodes, nrEdges, nrQueries, startNode;
    int fromNode, toNode, cost;
    int query;

    scanf("%d%d%d%d", &nrNodes, &nrEdges, &nrQueries, &startNode);

    while(nrNodes != 0 || nrEdges != 0 || nrQueries != 0 || startNode != 0){
        Bellman bellman = Bellman();
        Graph graph = Graph();

        graph.nrEdges = nrEdges;
        graph.nrNodes = nrNodes;

        for (int i = 0; i < nrEdges; ++i) {
            scanf("%d%d%d", &fromNode, &toNode, &cost);
            graph.addEdge(fromNode, toNode, cost);
        }

        pair<dataStructure, dataStructure> result = bellman.shortestPath(graph, startNode);

        dataStructure distanceMap = result.first;
        dataStructure prevMap = result.second;

        while(nrQueries--){
            scanf("%d", &query);
            if(query >= nrNodes) printf("%s\n", "Impossible");
            else if(distanceMap[query] == INT_MIN) printf("%s\n", "-Infinity");
            else if(distanceMap[query] == INT_MAX) printf("%s\n", "Impossible");
            else printf("%d\n", distanceMap[query]);
        }

        printf("\n");
        scanf("%d%d%d%d", &nrNodes, &nrEdges, &nrQueries, &startNode);
    }
    return 0;
}