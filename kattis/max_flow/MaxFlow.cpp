/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 23/2 - 18
 *
 *  Comments: Ford-Fulkerson algorithm for max flow. The initial graph should be a double array with all distances
 *              between all combinations, row-col. From node (row) to node (col).
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

struct Edge{
    int fromNode, toNode;
    long int capacity;
};

struct Node{
    vector<int> neighbours;
};

struct Graph{
    vector<Edge> edges;
    vector<Node> nodes;

    void addEdge(int &fromIndex, int &toIndex, long int &capacity){
        Edge e = Edge();
        e.fromNode = fromIndex;
        e.toNode = toIndex;
        e.capacity = capacity;
        edges.push_back(e);

        // Need to add reverse edge so we can traverse it if flow is full.
        nodes[fromIndex].neighbours.push_back(toIndex);
        nodes[toIndex].neighbours.push_back(fromIndex);
    };

    void addNode(int &node){
        Node n = Node();
        nodes.push_back(n);
    }
};

struct FordFulkerson{

    bool bfs(int &source, int &sink, int prev[], vector<vector<long int> > &residualEdges, Graph &graph) {
        bool visited[graph.nodes.size()];
        for (int i = 0; i < graph.nodes.size(); ++i) visited[i] = false;

        queue<int> q;
        q.push(source);
        visited[source] = true;

        // BFS loop
        while (!q.empty())
        {
            int from = q.front();
            q.pop();

            vector<int> *neighbours = &graph.nodes[from].neighbours;
            for (int i = 0; i < neighbours->size(); ++i) {
                int neighbour = (*neighbours)[i];
                if (!visited[neighbour] && residualEdges[from][neighbour] > 0)
                {
                    q.push(neighbour);
                    prev[neighbour] = from;
                    visited[neighbour] = true;
                }
            }
        }
        return visited[sink];
    }

    // Go through all possible edges and calculate the flow through that edge.
    vector<Edge> calcFlowGraph(Graph &graph, vector<vector<long int> > &edges,
                               vector<vector<long int> > &residualEdges){
        vector<Edge> res;
        for (int i = 0; i < graph.nodes.size(); ++i) {
            for (int j = 0; j < graph.nodes.size(); ++j) {
                if(edges[i][j] - residualEdges[i][j] > 0){
                    Edge e = Edge();
                    e.fromNode = i;
                    e.toNode = j;
                    e.capacity = edges[i][j] - residualEdges[i][j];
                    res.push_back(e);
                }
            }
        }
        return res;
    }

    pair<long int, vector<Edge> > maxFlow(Graph &graph, int &source, int &sink) {
        vector<vector<long int> > edges(graph.nodes.size(), (vector<long int>(graph.nodes.size(),0)));
        vector<vector<long int> > residualEdges(graph.nodes.size(), (vector<long int>(graph.nodes.size(),0)));

        for (auto e : graph.edges) {
            edges[e.fromNode][e.toNode] = e.capacity;
            residualEdges[e.fromNode][e.toNode] = e.capacity;
        }

        int prev[graph.nodes.size()];
        long int flow = 0;

        while(true)
        {
            // Check if there is a way from source to sink
            if(!bfs(source, sink, prev, residualEdges, graph)) break;

            // Calculate highest possible flow from source to sink
            bool firstRun = true;
            long int possibleFlow = 0;
            for (int to = sink; to != source; to = prev[to]) {
                int from = prev[to];
                if(firstRun){
                    possibleFlow = residualEdges[from][to];
                    firstRun = false;
                }else{
                    possibleFlow = min(possibleFlow, residualEdges[from][to]);
                }
            }

            // Update capacities
            for (int to = sink; to != source; to = prev[to]) {
                int from = prev[to];
                residualEdges[from][to] -= possibleFlow;
                residualEdges[to][from] += possibleFlow;
            }

            // Set flow
            flow += possibleFlow;
        }

        vector<Edge> flowGraph = calcFlowGraph(graph, edges, residualEdges);
        return make_pair(flow, flowGraph);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int nrNodes, nrEdges, source, sink;
    int fromNode, toNode;
    long int capacity;

    scanf("%d%d%d%d", &nrNodes, &nrEdges, &source, &sink);

    Graph graph = Graph();
    FordFulkerson fk = FordFulkerson();

    for (int i = 0; i < nrNodes; ++i) {
        graph.addNode(i);
    }
    for (int i = 0; i < nrEdges; ++i) {
        scanf("%d%d%ld", &fromNode, &toNode, &capacity);
        graph.addEdge(fromNode, toNode, capacity);
    }

    pair<long int, vector<Edge> > flow = fk.maxFlow(graph, source, sink);

    printf("%d %ld %d\n", nrNodes, flow.first, static_cast<int>(flow.second.size()));
    for (auto &i : flow.second) {
        printf("%d %d %ld\n", i.fromNode, i.toNode, i.capacity);
    }
    return 0;
}