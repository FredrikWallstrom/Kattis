/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 19/2 - 18
 *
 *  Comments: Floyd-Warshall. Used to get distance between two randomly selected nodes in a graph.
 *
 *  Lessons Learned: Be aware of some edge cases. For this we can have several edges between same nodes.
 *                  Need to take the edge with min cost.
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

const static int INF = 5000001;

struct Edge{
    int source, destination, cost;
};

struct Graph{
    int nrNodes{}, nrEdges{};
    vector<Edge> edges;
    int dist[150][150]{};
    int prev[150][150]{};

    void addEdge(int &source, int &destination, int &cost){
        Edge edge = Edge();
        edge.source = source;
        edge.destination = destination;
        edge.cost = cost;
        edges.push_back(edge);
    };
};

class FloydWarshall{

public:

    void shortestPath(Graph &graph) {

        // Initialize table with infinity.
        for (int i = 0; i < graph.nrNodes; ++i) {
            for (int j = 0; j < graph.nrNodes; ++j) {
                graph.dist[i][j] = INF;
                graph.prev[i][j] = NULL;
            }
        }

        // Place all distance, source -> destination, in table.
        // Place the min edge cost in table, if several edges between same nodes.
        for (int l = 0; l < graph.nrEdges; ++l) {
            Edge e = graph.edges[l];
            graph.dist[e.source][e.destination] = min(e.cost, graph.dist[e.source][e.destination]);
            graph.prev[e.source][e.destination] = e.destination;
        }

        // Set distance to itself to 0
        for (int k = 0; k < graph.nrNodes; ++k) {
            graph.dist[k][k] = 0;
        }

        // Main Floyd algorithm.
        for (int k = 0; k < graph.nrNodes; ++k) {
            for (int i = 0; i < graph.nrNodes; ++i) {
                for (int j = 0; j < graph.nrNodes; ++j) {
                    if(graph.dist[i][k] != INF && graph.dist[k][j] != INF &&
                            graph.dist[i][j] > graph.dist[i][k] + graph.dist[k][j]){
                        graph.dist[i][j] = graph.dist[i][k] + graph.dist[k][j];
                        graph.prev[i][j] = graph.prev[i][k];
                    }
                }
            }
        }

        // Negative cycles.
        for (int k = 0; k < graph.nrNodes; ++k) {
            // If this is true, then we got negative cycle.
            if (graph.dist[k][k] < 0) {
                for (int i = 0; i < graph.nrNodes; ++i) {
                    for (int j = 0; j < graph.nrNodes; ++j) {
                        // All pairs using k is in the negative cycle.
                        if (graph.dist[i][k] != INF && graph.dist[k][j] != INF) {
                            graph.dist[i][j] = -INF;
                            graph.prev[i][j] = -INF;
                        }
                    }
                }
            }
        }
    }

    string constructPath(Graph &graph, int &from, int &to){
        string path;
        if(graph.prev[from][to] == NULL || graph.prev[from][to] == -INF){
            // No Path
            return path;
        }

        path += to_string(from);
        while(from != to){
            from = graph.prev[from][to];
            path += to_string(from);
        }

        return path;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int nrNodes, nrEdges, nrQueries;
    int fromNode, toNode, cost;
    int from, to;

    scanf("%d%d%d", &nrNodes, &nrEdges, &nrQueries);

    while(nrNodes != 0 || nrEdges != 0 || nrQueries != 0){
        FloydWarshall floydWarshall = FloydWarshall();
        Graph graph = Graph();

        graph.nrEdges = nrEdges;
        graph.nrNodes = nrNodes;

        for (int i = 0; i < nrEdges; ++i) {
            scanf("%d%d%d", &fromNode, &toNode, &cost);
            graph.addEdge(fromNode, toNode, cost);
        }

        floydWarshall.shortestPath(graph);

        while(nrQueries--){
            scanf("%d%d", &from, &to);
            if(from >= nrNodes || to >= nrNodes) printf("%s\n", "Impossible");
            else if(graph.dist[from][to] == INF) printf("%s\n", "Impossible");
            else if(graph.dist[from][to] == -INF) printf("%s\n", "-Infinity");
            else printf("%d\n", graph.dist[from][to]);
        }

        printf("\n");
        scanf("%d%d%d", &nrNodes, &nrEdges, &nrQueries);
    }
    return 0;
}