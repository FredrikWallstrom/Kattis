/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 26/2 - 18
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
int locations;

struct Node{
    int id;
    bool visited = false;
    int stones;
    vector<pair<int, Node*> > neighbours;
};

struct Graph{
    map<int, Node> nodes;

    void addNode(int &node, int &stone){
        if(!nodes.count(node)){
            Node n = Node();
            n.id = node;
            n.stones = stone;
            nodes[node] = n;
        }
    }

    void addEdge(int &fromIndex, int &toIndex, int &cost){
        Node *fromNode = &nodes.at(fromIndex);
        Node *toNode = &nodes.at(toIndex);
        fromNode->neighbours.push_back(make_pair(cost, toNode));
    };
};

class Dijkstras{

public:

    pair<dataStructure, dataStructure> maxPickUp(Graph &graph, int startIndex, int &endIndex) {
        dataStructure distance;
        dataStructure stones;
        priority_queue< pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

        for (auto &node : graph.nodes) {
            node.second.visited = false;
            distance[node.second.id] = INT_MAX;
            stones[node.second.id] = 0;
        }

        distance[startIndex] = 0;
        stones[startIndex] = graph.nodes[startIndex].stones;
        pq.push(make_pair(distance[startIndex], startIndex));

        while(!pq.empty()){
            int currNodeIndex = pq.top().second;
            pq.pop();

            Node *currNode = &graph.nodes[currNodeIndex];
            currNode->visited = true;

            if(currNodeIndex == endIndex) break;

            for(int i = 0; i < currNode->neighbours.size(); ++i){
                pair<int, Node*> neighbour = currNode->neighbours[i];

                if(neighbour.second->visited) continue;

                if(distance[neighbour.second->id] > distance[currNode->id] + neighbour.first){

                    distance[neighbour.second->id] = distance[currNode->id] + neighbour.first;
                    stones[neighbour.second->id] = stones[currNode->id] + neighbour.second->stones;
                    pq.push(make_pair(distance[neighbour.second->id], neighbour.second->id));
                }
                else if(distance[neighbour.second->id] == distance[currNode->id] + neighbour.first){

                    if(stones[neighbour.second->id] < stones[currNode->id] + neighbour.second->stones){
                        distance[neighbour.second->id] = distance[currNode->id] + neighbour.first;
                        stones[neighbour.second->id] = stones[currNode->id] + neighbour.second->stones;
                        pq.push(make_pair(distance[neighbour.second->id], neighbour.second->id));

                    }
                }
            }
        }
        return make_pair(distance, stones);
    }
};
int main() {
    ios_base::sync_with_stdio(false);



    scanf("%d", &locations);
    vector<int> items(locations + 1);
    Graph graph = Graph();
    for (int i = 1; i <= locations; ++i) {
        int item;
        scanf("%d", &item);
        graph.addNode(i, item);
    }


    int roads;
    scanf("%d", &roads);

    for (int i = 0; i < roads; ++i) {
        int a,b,d;
        scanf("%d%d%d", &a, &b, &d);
        graph.addEdge(a, b, d);
        graph.addEdge(b, a, d);
    }

    Dijkstras dijkstras = Dijkstras();
    pair<dataStructure, dataStructure> result = dijkstras.maxPickUp(graph, 1, locations);

    if(result.first[locations] == INT_MAX){
        printf("impossible");
        return 0;
    }

    printf("%d %d", result.first[locations], result.second[locations]);



    return 0;
}