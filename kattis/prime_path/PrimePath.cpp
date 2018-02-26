
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
    bool visited = false;
    vector<pair<int,Node*> > neighbors;
    Node() {}
    
};

struct Graph {
    unordered_map<int,Node> vertices;
    Graph() {}
    
    void addNode(int &nodeId) {
        auto it = vertices.find(nodeId);
        
        if(it == vertices.end()) {
            Node newNode = Node();
            newNode.id = nodeId;
            vertices.insert(make_pair(nodeId, newNode));
        }
    }
    
    void addEdge(int &fromId, int &toId, int &weight) {
        Node* fromNode = &vertices.at(fromId);
        Node* toNode = &vertices.at(toId);
        fromNode->neighbors.push_back(make_pair(weight, toNode));
    }
};

struct Dijkstra {
    pair<unordered_map<int,int>, map<int,int> > shortestPathSingleNonNegative(Graph &graph, int &startId, int &end) {
        unordered_map<int,int> parents;
        map<int,int> distances;
        priority_queue<pair<int,int>, vector<pair<int, int> >, greater<pair<int,int>>> pq;
        for(int i = 0; i < graph.vertices.size() ; ++i) {
            graph.vertices[i].visited = false;
            distances[graph.vertices[i].id] = INT_MAX;
            parents[graph.vertices[i].id] = -1;
        }
        
        distances[startId] = 0;
        //priority queue contains pair with cost and node, where cost is the cost to reach that node from start.
        pq.push(make_pair(0,startId));
        
        while(!pq.empty()) {
            pair<int,int> currentNodePair = pq.top();
            pq.pop();
            
            Node* currNode = &graph.vertices[currentNodePair.second];
            currNode->visited = true;
            if(currNode->id == end) {
                break;
            }
            for(int i = 0; i < currNode->neighbors.size() ; ++i) {
                pair<int, Node*> neighbour = currNode->neighbors[i];
                if(neighbour.second->visited) {
                    continue;
                }
                // Compare node cost of neighbour with the distance to our curr node cost plus the cost to go to neighbor from currnode
                if(distances.at(neighbour.second->id) > currentNodePair.first + neighbour.first) {
                    distances.at(neighbour.second->id) = currentNodePair.first + neighbour.first;
                    parents.at(neighbour.second->id) = currentNodePair.second;
                    pq.push(make_pair(distances.at(neighbour.second->id),neighbour.second->id));
                }
            }
        }
        return make_pair(parents, distances);
    }
};



bool isPrime(int number) {
    for (int i = 2; i < number; ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

bool diffOne(int a, int b) {
    int count = 0;
    
    for (int i = 0; i < 4; ++i) {
        
        int digitA = int((a / pow(10.0, i))) % 10;
        int digitB = int((b / pow(10.0, i))) % 10;
        if(digitA != digitB){
            count++;
            if(count > 1){
                return false;
            }
        }
    }
    if(count != 1) {
        return false;
    }else {
        return true;
    }
}


int main() {

    
    vector<int> primeNumbers;
    Graph graph = Graph();
    for (int i = 1000; i < 10000; ++i) {
        if (isPrime(i)) {
            graph.addNode(i);
            primeNumbers.push_back(i);
        }
    }
    int cost = 1;
    for (int i = 0; i < primeNumbers.size(); ++i) {
        for (int j = i +1; j < primeNumbers.size(); ++j) {
            if(diffOne(primeNumbers[i], primeNumbers[j])) {
                graph.addEdge(primeNumbers[i], primeNumbers[j], cost);
                graph.addEdge(primeNumbers[j], primeNumbers[i], cost);
            }
        }
    }
    
    Dijkstra dk = Dijkstra();
    
    int testCases;
    scanf("%d", &testCases);
    
    for (int i = 0; i < testCases; ++i) {
        int start, end;
        scanf("%d %d", &start, &end);
        pair<unordered_map<int,int>, map<int,int> > res = dk.shortestPathSingleNonNegative(graph, start, end);
        if(res.second[end] == INT_MAX) {
            printf("Impossible\n");
        }else  {
            printf("%d\n",res.second[end]);
        }
        
    }
    return 0;
}