/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 21/2 - 18
 *
 *  Comments: MST, kruskals algorithm.
 *
 *  Lessons Learned: New operator is OK, just if time limit we need to think about it since it takes alot of time to
 *                  make a new object with new.
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
    int fromNode, toNode, cost;

    bool operator<(Edge other) const
    {
        return cost < other.cost;
    }
};

struct Subset {
    int size;
    Subset *parent;
};

struct Graph{
    vector<Edge> edges;
    int nrNodes{}, nrEdges{};

    vector<Subset*> subsets;

    void addEdge(int &fromIndex, int &toIndex, int &cost){
        Edge edge = Edge();
        edge.fromNode = fromIndex;
        edge.toNode = toIndex;
        edge.cost = cost;
        edges.push_back(edge);
    };
};

class Mst{

public:
    pair<int, vector<Edge> > shortestPath(Graph &graph) {
        int index = 0;
        int totCost = 0;
        vector<Edge> mst;
        sort(graph.edges.begin(), graph.edges.end());

        for (int i = 0; i < graph.nrNodes; ++i) {
            auto *s = new Subset();
            s->parent = nullptr;
            s->size = 1;
            graph.subsets.push_back(s);
        }

        while(mst.size() < graph.nrNodes - 1){

            if(index == graph.edges.size()){
                mst.clear();
                Edge e = Edge();
                e.cost = -1;
                mst.push_back(e);
                break;
            }

            Edge *e = &graph.edges[index++];
            Subset *s1 = findRoot(graph, e->fromNode);
            Subset *s2 = findRoot(graph, e->toNode);

            if (s1 != s2) {
                mst.push_back(*e);
                totCost += e->cost;
                unionCall(s1, s2);
            }
        }

        return make_pair(totCost, mst);
    }

    Subset* findRoot(Graph &graph, int &value) {
        while(graph.subsets[value]->parent != nullptr){
            // Path compression
            graph.subsets[value] = graph.subsets[value]->parent;
        }
        return graph.subsets[value];
    }

    void unionCall(Subset *rootA, Subset *rootI) {

        // a and i is already union.
        if(rootA == rootI) return;

        // Join the smaller subset, with the larger one.
        if(rootA->size < rootI->size){
            rootA->parent = rootI;
            rootI->size += rootA->size;
            rootA->size = 0;
        }else{
            rootI->parent = rootA;
            rootA->size += rootI->size;
            rootI->size = 0;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int nrNodes, nrEdges;
    int fromNode, toNode, cost;

    scanf("%d%d", &nrNodes, &nrEdges);

    while(nrNodes != 0 || nrEdges != 0){
        Mst mst = Mst();
        Graph graph = Graph();

        graph.nrNodes = nrNodes;
        graph.nrEdges = nrEdges;

        while(nrEdges--){
            scanf("%d%d%d", &fromNode, &toNode, &cost);
            graph.addEdge(fromNode, toNode, cost);
        }

        pair<int, vector<Edge> > res = mst.shortestPath(graph);

        int cost = res.first;
        vector<Edge> edges = res.second;

        if(edges[0].cost == -1){
            printf("%s\n" ,"Impossible");
        }else{
            printf("%d\n", cost);

            pair<int,int> rightOrder[nrNodes - 1];

            for (int i = 0; i < nrNodes - 1; ++i) {
                rightOrder[i].first = min(edges[i].fromNode, edges[i].toNode);
                rightOrder[i].second = max(edges[i].fromNode, edges[i].toNode);
            }

            sort(rightOrder, rightOrder+(graph.nrNodes-1));

            for (int i = 0; i < graph.nrNodes - 1; ++i){
                printf("%d ", rightOrder[i].first);
                printf("%d\n", rightOrder[i].second);
            }
        }
        scanf("%d%d", &nrNodes, &nrEdges);

    }
    return 0;
}