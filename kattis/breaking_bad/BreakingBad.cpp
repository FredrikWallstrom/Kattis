
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

struct Node{
    int color = -1;
    vector<int> neighbours;
    int id;
};

struct Graph {
    vector<Node> nodes;

    void addNode(int &nodeId) {
        Node newNode = Node();
        newNode.id = nodeId;
        nodes.push_back(newNode);
    }

    void addEdge(int &fromId, int &toId) {
        nodes[fromId].neighbours.push_back(toId);
    }
};

bool bipartite(Graph &graph, int startNode) {
    queue<int> q;
    q.push(startNode);
    int color = 0;
    graph.nodes[startNode].color = color;

    while(!q.empty()) {
        int current = q.front();
        q.pop();

        if(graph.nodes[current].color == 0) {
            color = 1;
        }else {
            color = 0;
        }

        for (int j = 0; j < graph.nodes[current].neighbours.size(); ++j) {
            int neighbour = graph.nodes[current].neighbours[j];
            if(graph.nodes[neighbour].color != -1 && graph.nodes[neighbour].color != color){
                return false;
            } else if (graph.nodes[neighbour].color == -1) {
                graph.nodes[neighbour].color = color;
                q.push(graph.nodes[neighbour].id);
            }
        }
    }
    return true;
}

int main()
{

    int N, M;
    cin >> N;
    map<int, string> nodeToString;
    map<string,int> stringToNode;
    Graph graph = Graph();
    for (int i = 0; i < N; i++)
    {
        string s;
        cin >> s;
        graph.addNode(i);

        stringToNode.insert(make_pair(s, i));
        nodeToString.insert(make_pair(i, s));
    }

    cin >> M;
    for (int i = 0; i < M; i++)
    {
        string s1, s2;
        cin >> s1 >> s2;

        graph.addEdge(stringToNode[s1], stringToNode[s2]);
        graph.addEdge(stringToNode[s2], stringToNode[s1]);
    }


    for (int i = 0; i < graph.nodes.size(); ++i) {
        if(graph.nodes[i].color != -1) {
            continue;
        }

        if(!bipartite(graph, i)) {
            cout << "impossible" << endl;
            return 0;
        }
    }

    for (int i = 0; i < N; i++) {

        if(graph.nodes[i].color == 0) {
            cout << nodeToString[i] << " ";
        }
    }

    cout << endl;

    for (int i = 0; i < N; i++) {
        if(graph.nodes[i].color == 1) {
            cout << nodeToString[i] << " ";
        }
    }
    return 0;
}
