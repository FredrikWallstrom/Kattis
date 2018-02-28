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
    int fromNode, toNode;
    double cost;

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

    void addEdge(int &fromIndex, int &toIndex, double &cost){
        Edge edge = Edge();
        edge.fromNode = fromIndex;
        edge.toNode = toIndex;
        edge.cost = cost;
        edges.push_back(edge);
    };
};

class Mst{

public:
    pair<double, vector<Edge> > shortestPath(Graph &graph) {
        int index = 0;
        double totCost = 0;
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
    ios_base::sync_with_stdio(false);
    int testcases, nrOfPoints;
    scanf("%d", &testcases);

    for (int i = 0; i < testcases; ++i) {

        scanf("%d", &nrOfPoints);
        Graph graph = Graph();

        graph.nrNodes = nrOfPoints;
        vector<Point> freckles;

        for (int j = 0; j < nrOfPoints; ++j) {
            double x, y;
            scanf("%lf %lf", &x, &y);
            Point point = Point();
            point.x = x;
            point.y = y;
            freckles.push_back(point);
        }

        for(int k = 0; k < freckles.size(); ++k) {
            for (int z  = k + 1; z < freckles.size() ; ++z) {
                double distance = calculateDistance(freckles[k], freckles[z]);
                graph.addEdge(k, z, distance);
            }
        }

        Mst mst = Mst();
        pair<double, vector<Edge> > result = mst.shortestPath(graph);
        printf("%.2lf\n\n", result.first);
    }
    return 0;
}