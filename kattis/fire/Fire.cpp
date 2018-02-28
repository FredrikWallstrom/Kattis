

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
typedef vector<int> dataStructure;

struct Node{
    int id;
    bool visited = false;
    vector<pair<int,int> > neighbours;
};

struct Graph{
    vector<Node> nodes;

    void addNode(int &node){
        Node n = Node();
        n.id = node;
        nodes.push_back(n);
    }

    void addEdge(int &fromIndex, int &toIndex, int cost){
        nodes[fromIndex].neighbours.push_back(make_pair(cost,toIndex));
    };
};

class Dijkstras{

public:

    dataStructure shortestPath(Graph &graph, vector<int> &startIndices) {
        dataStructure distance(graph.nodes.size(), INT_MAX);
        priority_queue< pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

        for (auto &node : graph.nodes) {
            node.visited = false;
        }

        for (int i = 0; i < startIndices.size(); ++i) {
            distance[startIndices[i]] = 0;
            pq.push(make_pair(distance[startIndices[i]], startIndices[i]));
        }


        while(!pq.empty()){
            int currNodeIndex = pq.top().second;
            pq.pop();

            graph.nodes[currNodeIndex].visited = true;

            for(int i = 0; i < graph.nodes[currNodeIndex].neighbours.size(); ++i){
                pair<int,int> neighbour = graph.nodes[currNodeIndex].neighbours[i];

                if(graph.nodes[neighbour.second].visited) continue;

                if(distance[neighbour.second] > distance[currNodeIndex] + neighbour.first){
                    distance[neighbour.second] = distance[currNodeIndex] + neighbour.first;
                    pq.push(make_pair(distance[neighbour.second], neighbour.second));
                }
            }
        }
        return distance;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int nrOfRow, nrOfCol;


    cin >> nrOfRow >> nrOfCol;
    int board[nrOfRow][nrOfCol];
    char piece;
    Graph graph = Graph();

    int nodeMap[nrOfRow][nrOfCol];
    int count = 0;

    vector<pair<int, int> > directions;
    directions.push_back(make_pair(1, 0));
    directions.push_back(make_pair(0, 1));
    directions.push_back(make_pair(-1, 0));
    directions.push_back(make_pair(0, -1));


    vector<int> startJ;
    vector<int> startFire;

    for (int row = 0; row < nrOfRow; ++row) {
        for (int col = 0; col < nrOfCol; ++col) {
            graph.addNode(count);
            cin >> piece;
            board[row][col] = piece;
            nodeMap[row][col] = count;
            if(piece == 'J') startJ.push_back(count);
            if(piece == 'F') startFire.push_back(count);
            count++;
        }
    }

    for (int k = 0; k < nrOfRow; ++k) {
        for (int i = 0; i < nrOfCol; ++i) {
            for (int j = 0; j < directions.size(); ++j) {
                int row = k + directions[j].first;
                int col = i + directions[j].second;
                if(row >= 0 && col >= 0 && row < nrOfRow && col < nrOfCol && board[row][col] == '.'){
                    graph.addEdge(nodeMap[k][i], nodeMap[row][col], 1);
                }
            }
        }
    }

    Dijkstras dijkstras = Dijkstras();
    dataStructure distanceJ = dijkstras.shortestPath(graph, startJ);
    dataStructure distanceFire = dijkstras.shortestPath(graph, startFire);

    int minDistance = INT_MAX;
    for (int i = 0; i < nrOfRow; ++i) {
        if(board[i][0] != '#' && distanceJ[nodeMap[i][0]] < distanceFire[nodeMap[i][0]]){
            minDistance = min(minDistance, distanceJ[nodeMap[i][0]] + 1);
        }

        if(board[i][nrOfCol-1] != '#' && distanceJ[nodeMap[i][nrOfCol-1]] < distanceFire[nodeMap[i][nrOfCol-1]]){
            minDistance = min(minDistance, distanceJ[nodeMap[i][nrOfCol-1]] + 1);
        }
    }

    for (int i = 0; i < nrOfCol; ++i) {
        if(board[0][i] != '#' && distanceJ[nodeMap[0][i]] < distanceFire[nodeMap[0][i]]) {
            minDistance = min(minDistance, distanceJ[nodeMap[0][i]] + 1);
        }

        if(board[nrOfRow-1][i] != '#' && distanceJ[nodeMap[nrOfRow-1][i]] < distanceFire[nodeMap[nrOfRow-1][i]]) {
            minDistance = min(minDistance, distanceJ[nodeMap[nrOfRow - 1][i]] + 1);
        }
    }

    if(minDistance == INT_MAX) cout << "IMPOSSIBLE";
    else cout << minDistance;


    return 0;
}
