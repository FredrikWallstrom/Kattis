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
const static int nrOfRows = 500;
const static int nrOfColumns = 500;

struct Edge{
    int fromNode, toNode;
    long int capacity;
};

struct Graph{
    unordered_map<int, vector<int> > neighbours;
    int nrNodes;
    long int edges[nrOfRows][nrOfColumns]{};
    long int residualEdges[nrOfRows][nrOfColumns]{};

    void addEdge(int &fromIndex, int &toIndex, long int &capacity){
        edges[fromIndex][toIndex] = capacity;
        residualEdges[fromIndex][toIndex] = capacity;
        neighbours[fromIndex].push_back(toIndex);

        // Need to add reverse edge so we can traverse it if flow is full.
        neighbours[toIndex].push_back(fromIndex);
    };
};

struct FordFulkerson{

    bool bfs(int &source, int &sink, int prev[], Graph &graph) {
        bool visited[graph.nrNodes];
        for (int i = 0; i < graph.nrNodes; ++i) visited[i] = false;

        queue<int> q;
        q.push(source);
        visited[source] = true;

        // BFS loop
        while (!q.empty())
        {
            int from = q.front();
            q.pop();
            vector<int> neighbours = graph.neighbours[from];
            for (int neighbour : neighbours) {
                if (!visited[neighbour] && graph.residualEdges[from][neighbour] > 0)
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
    vector<Edge> calcFlowGraph(Graph &graph){
        vector<Edge> res;
        for (int i = 0; i < graph.nrNodes; ++i) {
            for (int j = 0; j < graph.nrNodes; ++j) {
                if(graph.edges[i][j] - graph.residualEdges[i][j] > 0){
                    Edge e = Edge();
                    e.fromNode = i;
                    e.toNode = j;
                    e.capacity = graph.edges[i][j] - graph.residualEdges[i][j];
                    res.push_back(e);
                }
            }
        }
        return res;
    }

    pair<long int, vector<Edge> > maxFlow(Graph &graph, int &source, int &sink) {
        int prev[graph.nrNodes];
        long int flow = 0;

        while(true)
        {
            // Check if there is a way from source to sink
            if(!bfs(source, sink, prev, graph)) break;

            // Calculate highest possible flow from source to sink
            bool firstRun = true;
            long int possibleFlow = 0;
            for (int to = sink; to != source; to = prev[to]) {
                int from = prev[to];
                if(firstRun){
                    possibleFlow = graph.residualEdges[from][to];
                    firstRun = false;
                }else{
                    possibleFlow = min(possibleFlow, graph.residualEdges[from][to]);
                }
            }

            // Update capacities
            for (int to = sink; to != source; to = prev[to]) {
                int from = prev[to];
                graph.residualEdges[from][to] -= possibleFlow;
                graph.residualEdges[to][from] += possibleFlow;
            }

            // Set flow
            flow += possibleFlow;
        }

        vector<Edge> flowGraph = calcFlowGraph(graph);
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

    graph.nrNodes = nrNodes;

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