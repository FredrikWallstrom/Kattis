

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
int board[8][8];

struct Node{
    int id;
    int direction = -1;
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

int rotateTo(int fromRow, int fromCol, int toRow, int toCol) {
    if(fromRow == toRow){
        if(fromCol < toCol){
            return 1;
        }else{
            return 3;
        }
    }else{
        if(fromRow < toRow){
            return 2;
        }else{
            return 0;
        }
    }
}

class Dijkstras{

public:

    pair<dataStructure, dataStructure> shortestPath(Graph &graph, int &startIndex, int &endIndex, map<int, pair<int, int> > &nodeToCord) {
        dataStructure distance(graph.nodes.size(), INT_MAX);
        dataStructure prev(graph.nodes.size(), -1);
        priority_queue< pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

        for (auto &node : graph.nodes) {
            node.visited = false;
        }

        distance[startIndex] = 0;
        pq.push(make_pair(distance[startIndex], startIndex));
        prev[startIndex] = startIndex;

        graph.nodes[startIndex].direction = 1;

        while(!pq.empty()){
            int currNodeIndex = pq.top().second;
            pq.pop();

            graph.nodes[currNodeIndex].visited = true;
            if(currNodeIndex == endIndex) {
                break;
            }

            for(int i = 0; i < graph.nodes[currNodeIndex].neighbours.size(); ++i){
                pair<int,int> neighbour = graph.nodes[currNodeIndex].neighbours[i];

                pair<int, int> neighbourCord = nodeToCord[neighbour.second];
                int rotation = rotateTo(nodeToCord[currNodeIndex].first, nodeToCord[currNodeIndex].second,
                    neighbourCord.first, neighbourCord.second);
                int extraCost = 0;
                if(rotation != graph.nodes[currNodeIndex].direction){
                    extraCost += 1;
                }
                if(board[neighbourCord.first][neighbourCord.second] == 'I'){
                    extraCost += 1;
                }

                if(graph.nodes[neighbour.second].visited) continue;

                if(distance[neighbour.second] > distance[currNodeIndex] + neighbour.first + extraCost){
                    distance[neighbour.second] = distance[currNodeIndex] + neighbour.first + extraCost;
                    prev[neighbour.second] = currNodeIndex;

                    graph.nodes[neighbour.second].direction = rotation;

                    pq.push(make_pair(distance[neighbour.second], neighbour.second));
                }
            }
        }
        return make_pair(distance, prev);
    }
};



int main() {
    ios_base::sync_with_stdio(false);


    char piece;
    Graph graph = Graph();

    int nodeMap[8][8];
    map<int, pair<int, int> > nodeToCord;
    int count = 0;

    vector<pair<int, int> > directions;
    directions.push_back(make_pair(1, 0));
    directions.push_back(make_pair(0, 1));
    directions.push_back(make_pair(-1, 0));
    directions.push_back(make_pair(0, -1));

    int start;
    int end;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            graph.addNode(count);
            cin >> piece;
            board[row][col] = piece;
            nodeMap[row][col] = count;
            nodeToCord[count] = make_pair(row, col);
            if(piece == 'T') start = count;
            if(piece == 'D') end = count;
            count++;
        }
    }

    for (int k = 0; k < 8; ++k) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < directions.size(); ++j) {
                int row = k + directions[j].first;
                int col = i + directions[j].second;
                if(row >= 0 && col >= 0 && row < 8 && col < 8 && board[row][col] != 'C'){
                    graph.addEdge(nodeMap[k][i], nodeMap[row][col], 1);
                }
            }
        }
    }

    Dijkstras dijkstras = Dijkstras();
    pair<dataStructure, dataStructure> res = dijkstras.shortestPath(graph, start, end, nodeToCord);

    dataStructure distance = res.first;
    dataStructure path = res.second;

    if(distance[end] == INT_MAX){
        cout << "no solution";
        return 0;
    }

    stack<int> tmpStack;
    tmpStack.push(end);
    int tmp = end;
    while(true){
        int curr = path[tmp];
        tmpStack.push(curr);
        if(curr == start) break;
        tmp = curr;
    }

    vector<pair<int, int> > shortestPath;
    while(!tmpStack.empty()){
        shortestPath.push_back(nodeToCord[tmpStack.top()]);
        tmpStack.pop();
    }

    vector<char> result;
    int currentRot = 1;
    for (int i = 0; i < shortestPath.size()-1; ++i) {
        int goToRotate = rotateTo(shortestPath[i].first, shortestPath[i].second, shortestPath[i+1].first, shortestPath[i+1].second);

        if(currentRot == 0) {
            if(goToRotate == 1){
                result.push_back('R');
            }else if(goToRotate == 3){
                result.push_back('L');
            }

        }else if(currentRot == 3) {
            if (goToRotate == 0) {
                result.push_back('R');
            } else if (goToRotate == 2) {
                result.push_back('L');
            }
        }else if(currentRot < goToRotate){
            result.push_back('R');
        }else if(currentRot > goToRotate){
            result.push_back('L');
        }

        currentRot = goToRotate;

        if(board[shortestPath[i+1].first][shortestPath[i+1].second] == 'I'){
            result.push_back('X');
            result.push_back('F');
        }else{
            result.push_back('F');
        }
    }
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i];
    }

    return 0;
}
