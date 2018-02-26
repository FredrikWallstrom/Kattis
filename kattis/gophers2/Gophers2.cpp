#include <stdio.h>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <map>
#include <math.h>
#include <float.h>
#include <queue>
#include <limits.h>
#include <unordered_map>
#include <ctime>
#include <stack>


using namespace std;

struct Node {
    int id;
    vector<int> neighbors;
};

struct Edge {
    int src;
    int dest;
    long long int capacity;
};

struct Graph {
    vector<Edge> edges;
    vector<Node> nodes;
    Graph() {}
    
    void addNode(int &nodeId) {
        Node newNode = Node();
        newNode.id = nodeId;
        nodes.push_back(newNode);
    }
    
    void addEdge(int fromId, int toId, long long int capacity) {
        Edge edge = Edge();
        edge.src = fromId;
        edge.dest = toId;
        edge.capacity = capacity;
        edges.push_back(edge);
        
        //This is used for the BFS search, although we have a directed graph we add
        //neighbours in both directions because we can decrease a flow.
        nodes[fromId].neighbors.push_back(nodes[toId].id);
        nodes[toId].neighbors.push_back(nodes[fromId].id);
        
    }
};

struct FordFulkerson {
    
    bool bfs(vector<vector<long long int> > &residualCapacity ,vector<int> &parent, int &start, int &goal, Graph &graph) {
        queue<int> q;
        vector<int> visited(residualCapacity.size(),0);
        
        q.push(start);
        visited[start] = 1;
        parent[start] = -1;
        
        while(!q.empty()) {
            int current = q.front();
            q.pop();
            
            for(int i = 0; i < graph.nodes[current].neighbors.size() ; ++i) {
                int currentNeighbour = graph.nodes[current].neighbors[i];
                if(!visited[currentNeighbour] && residualCapacity[current][currentNeighbour] > 0) {
                    visited[currentNeighbour] = 1;
                    q.push(currentNeighbour);
                    parent[currentNeighbour] = current;
                    
                    if(visited[goal]) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    
    pair<long long int, vector<Edge> > maximumFlow(Graph &graph, int source, int sink) {
        vector<vector<long long int> > capacity(graph.nodes.size(), (vector<long long int>(graph.nodes.size(),0)));
        vector<vector<long long int> > residualCapacity(graph.nodes.size(), (vector<long long int>(graph.nodes.size(),0)));
        vector<int> parent(graph.nodes.size());
        vector<Edge> flows;
        long long int maxFlow = 0;
        
        //Step 1 initialize
        for(Edge edge : graph.edges) {
            residualCapacity[edge.src][edge.dest] = edge.capacity;
            capacity[edge.src][edge.dest] = edge.capacity;
        }
        
        
        while(bfs(residualCapacity, parent, source, sink, graph)) {
            
            //find lowest residual capacity on the path found by BFS
            long long int lowestFlow = INT_MAX;
            int u = sink;
            int v = sink;
            while(v != source) {
                u = parent[v];
                long long int rc = residualCapacity[u][v];
                if(rc < lowestFlow) {
                    lowestFlow = rc;
                }
                v = u;
            }
            
            u = sink;
            v = sink;
            while (v != source) {
                u = parent[v];
                residualCapacity[u][v] -= lowestFlow;
                residualCapacity[v][u] += lowestFlow;
                
                v = u;
            }
            
            maxFlow += lowestFlow;
        }
        
        //Add all edges that send "units" over the edges.
        for(int i = 0; i < capacity.size(); ++i) {
            for(int j = 0; j < capacity.size(); ++j) {
                if(residualCapacity[i][j] < capacity[i][j]) {
                    Edge edge = Edge();
                    edge.src = i;
                    edge.dest = j;
                    edge.capacity = capacity[i][j] - residualCapacity[i][j];
                    flows.push_back(edge);
                }
            }
        }
        return make_pair(maxFlow, flows);
    }
    
};

struct Point {
    double x;
    double y;
};

double calculateDistance(Point pointOne, Point pointTwo) {
    double a = pointOne.x - pointTwo.x;
    double b = pointOne.y - pointTwo.y;
    return sqrt(a*a + b*b);
}


int main() {

    int nrOfGophers, nrOfHoles, seconds, velocity;

    while(scanf("%d %d %d %d", &nrOfGophers, &nrOfHoles, &seconds, &velocity) == 4) {

        vector<Point> gopherPositions;
        vector<Point> holePositions;
        for (int i = 0; i < nrOfGophers; ++i) {
            double x, y;
            scanf("%lf %lf", &x, &y);
            Point point = Point();
            point.x = x;
            point.y = y;
            gopherPositions.push_back(point);
        }

        for (int i = 0; i < nrOfHoles; ++i) {
            double x, y;
            scanf("%lf %lf", &x, &y);
            Point point = Point();
            point.x = x;
            point.y = y;
            holePositions.push_back(point);
        }

        Graph graph = Graph();
        for (int i = 0; i < nrOfGophers + nrOfHoles + 2 ; ++i) {
            graph.addNode(i);
        }

        //create edges
        int edgeNumbers[nrOfGophers][nrOfHoles];
        int count = 0;
        for (int i = 1; i <= nrOfGophers+nrOfHoles; ++i) {
            if(i <= nrOfGophers) {
                graph.addEdge(0, i, 1);
                count++;
                for (int j = 1; j <= nrOfHoles; ++j) {
                    edgeNumbers[i-1][j-1] = count;
                    graph.addEdge(i, j+nrOfGophers, 0);
                    count++;
                }
            } else {
                graph.addEdge(i, nrOfGophers+nrOfHoles+1, 1);
            }
        }

        for (int r = 0; r < nrOfGophers; ++r) {
            for (int h = 0; h < nrOfHoles; ++h) {
                double distance = calculateDistance(gopherPositions[r], holePositions[h]);
                if(velocity*seconds >= distance) {
                    graph.edges[edgeNumbers[r][h]].capacity = 1;
                } else {
                    graph.edges[edgeNumbers[r][h]].capacity = 0;

                }
            }
        }
        FordFulkerson fk = FordFulkerson();
        pair<long long int, vector<Edge> > res = fk.maximumFlow(graph, 0, nrOfHoles+nrOfGophers+1);
        printf("%lld\n", nrOfGophers - res.first);
    }
    return 0;
}








