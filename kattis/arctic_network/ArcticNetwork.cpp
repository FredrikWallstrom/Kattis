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

struct Edge;

struct Node {
    int id;
    vector<Edge> neighbors;
    bool operator<(Node const& rhs) const {
        return true;
    }
};

struct Edge {
    Node* src;
    Node* dest;
    double weight;
    
    bool operator<(Edge other) const
    {
        return weight < other.weight;
    }
};



struct Graph {
    //    vector<Edge> edges;
    vector<Node> nodes;
    Graph() {}
    
    void addNode(int &nodeId) {
        Node newNode = Node();
        newNode.id = nodeId;
        nodes.push_back(newNode);
    }
    
    void addEdge(int &u, int &v, double &weight) {
        Edge edge = Edge();
        
        if( u == v) {
            return;
        }
        
        Node *nodeOne = &nodes[u];
        Node *nodeTwo = &nodes[v];
        edge.src = nodeOne;
        edge.dest = nodeTwo;
        edge.weight = weight;
        nodeOne->neighbors.push_back(edge);
        edge.src = nodeTwo;
        edge.dest = nodeOne;
        nodeTwo->neighbors.push_back(edge);
    }
};

struct Prim {
    
    
    vector<Edge> primMinimumSpanningTree(Graph &graph) {
        unordered_map<int,Edge> bestEdges;
        priority_queue<pair<int,Node> ,vector<pair<int, Node> >, greater<pair<int, Node>> > pq;
        vector<bool> isInTree(graph.nodes.size(),false);
        vector<Edge> result;
        vector<int> costsForNode(graph.nodes.size(), INT_MAX);
        
        //Start with first node in nodes list.
        pq.push(make_pair(0, graph.nodes[0]));
        
        //Special case for the first node we start with, we know that it have to be in the tree so we set its flag to be so
        // it will be added to the result tree through one of its neighbors
        isInTree[0] = true;
        while(!pq.empty()) {
            pair<int,Node> current = pq.top();
            pq.pop();
            
            //whenever we pop a node we know that the cheapest way is found.
            if(bestEdges.find(current.second.id) != bestEdges.end() && !isInTree[current.second.id]) {
                result.push_back(bestEdges.at(current.second.id));
                isInTree[current.second.id] = true;
                
            }
            
            for(Edge &edge : current.second.neighbors) {
                Node* v = edge.dest;
                if(!isInTree[v->id] && costsForNode[v->id] > edge.weight) {
                    costsForNode[v->id] = edge.weight;
                    pq.push(make_pair(edge.weight, *v));
                    bestEdges[v->id] = edge;
                }
            }
        }
        return result;
    }
    
    
    vector<Edge> sortEdgeIndexes(vector<Edge> edges) {
        vector<Edge> res;
        for(int i = 0; i < edges.size(); ++i) {
            Edge edge = Edge();
            if(edges[i].src->id > edges[i].dest->id) {
                edge.dest = edges[i].src;
                edge.src = edges[i].dest;
            }else {
                edge.dest = edges[i].dest;
                edge.src = edges[i].src;
            }
            res.push_back(edge);
        }
        return res;
    }
};

struct Point {
    int x;
    int y;
};



struct EdgeLexicographic {
    inline bool operator() (const Edge& e1, const Edge& e2) {
        if(e1.src->id != e2.src->id){
            return e1.src->id < e2.src->id;
        } else {
            return e1.dest->id < e2.dest->id;
        }
    }
};

double calculateDistance(Point pointOne, Point pointTwo) {
    int a = pointOne.x - pointTwo.x;
    int b = pointOne.y - pointTwo.y;
    return sqrt(a*a + b*b);
}

int main() {
    int testcases, satellites, nrOfOutposts;
    scanf("%d", &testcases);
    for (int i = 0; i < testcases; ++i) {
        
        scanf("%d %d", &satellites, &nrOfOutposts);
        
        Graph graph = Graph();
        //this method requires that nodes are "named" 0 to n-1
        for (int i = 0; i < nrOfOutposts; i++) {
            graph.addNode(i);
        }
        
        vector<Point> outposts;
        
        for (int j = 0; j < nrOfOutposts; ++j) {
            int x, y;
            scanf("%d %d", &x, &y);
            Point point = Point();
            point.x = x;
            point.y = y;
            outposts.push_back(point);
        }
        
        for(int k = 0; k < outposts.size(); ++k) {
            for (int z  = k + 1; z < outposts.size() ; ++z) {
                double distance = calculateDistance(outposts[k], outposts[z]);
                graph.addEdge(k, z, distance);
            }
        }
        
        Prim pr = Prim();
        vector<Edge> result = pr.primMinimumSpanningTree(graph);
        sort(result.begin(), result.end());
        double cost = result[result.size() - satellites].weight;
        printf("%.2f\n", cost);
    }
    return 0;
}





