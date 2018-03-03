/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 1/3 - 18
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

int maxScore = 0;
int nrOfTeams, nrOfRemainingMatches;

struct Edge{
    int fromNode, toNode;
    int capacity;
};

struct Node{
    vector<int> neighbours;
};

struct Graph{
    vector<Edge> edges;
    vector<Node> nodes;

    void addEdge(int fromIndex, int toIndex, int capacity){
        Edge e = Edge();
        e.fromNode = fromIndex;
        e.toNode = toIndex;
        e.capacity = capacity;
        edges.push_back(e);

        // Need to add reverse edge so we can traverse it if flow is full.
        nodes[fromIndex].neighbours.push_back(toIndex);
        nodes[toIndex].neighbours.push_back(fromIndex);
    };

    void addNode(int &node){
        Node n = Node();
        nodes.push_back(n);
    }
};

struct FordFulkerson{

    bool bfs(int &source, int &sink, int prev[], vector<vector<int> > &residualEdges, Graph &graph) {
        bool visited[graph.nodes.size()];
        for (int i = 0; i < graph.nodes.size(); ++i) visited[i] = false;

        queue<int> q;
        q.push(source);
        visited[source] = true;

        // BFS loop
        while (!q.empty())
        {
            int from = q.front();
            q.pop();

            vector<int> *neighbours = &graph.nodes[from].neighbours;
            for (int i = 0; i < neighbours->size(); ++i) {
                int neighbour = (*neighbours)[i];
                if (!visited[neighbour] && residualEdges[from][neighbour] > 0)
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
    vector<Edge> calcFlowGraph(Graph &graph, vector<vector<int> > &edges,
                               vector<vector<int> > &residualEdges){
        vector<Edge> res;
        for (int i = 0; i < graph.nodes.size(); ++i) {
            for (int j = 0; j < graph.nodes.size()-1; ++j) {
                if(i == 0) continue;
                if(edges[i][j] - residualEdges[i][j] > 0){
                    Edge e = Edge();
                    e.fromNode = i;
                    e.toNode = j;
                    e.capacity = edges[i][j] - residualEdges[i][j];
                    res.push_back(e);
                }
            }
        }
        return res;
    }

    pair<int, vector<Edge> > maxFlow(Graph &graph, int source, int sink) {
        vector<vector<int> > edges(graph.nodes.size(), (vector<int>(graph.nodes.size(),0)));
        vector<vector<int> > residualEdges(graph.nodes.size(), (vector<int>(graph.nodes.size(),0)));

        for (auto e : graph.edges) {
            edges[e.fromNode][e.toNode] = e.capacity;
            residualEdges[e.fromNode][e.toNode] = e.capacity;
        }

        int prev[graph.nodes.size()];
        int flow = 0;

        while(true)
        {
            // Check if there is a way from source to sink
            if(!bfs(source, sink, prev, residualEdges, graph)) break;

            // Calculate highest possible flow from source to sink
            bool firstRun = true;
            int possibleFlow = 0;
            for (int to = sink; to != source; to = prev[to]) {
                int from = prev[to];
                if(firstRun){
                    possibleFlow = residualEdges[from][to];
                    firstRun = false;
                }else{
                    possibleFlow = min(possibleFlow, residualEdges[from][to]);
                }
            }

            // Update capacities
            for (int to = sink; to != source; to = prev[to]) {
                int from = prev[to];
                residualEdges[from][to] -= possibleFlow;
                residualEdges[to][from] += possibleFlow;
            }

            // Set flow
            flow += possibleFlow;
        }

        vector<Edge> flowGraph = calcFlowGraph(graph, edges, residualEdges);
        return make_pair(flow, flowGraph);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int score, teamOne, teamTwo;

    while(true) {
        scanf("%d", &nrOfTeams);
        if (nrOfTeams == -1) break;
        scanf("%d", &nrOfRemainingMatches);

        int scoreOther = 0;
        vector<int> leagueTable(static_cast<unsigned long>(nrOfTeams + 1));
        vector<pair<int, int> > gamesLeft;

        for (int i = 1; i <= nrOfTeams; ++i) {
            scanf("%d", &score), leagueTable[i] = score;
            if (i == nrOfTeams) maxScore = score;
            else scoreOther = max(scoreOther, score);
        }

        vector<pair<int, int> > allGames;
        for (int i = 1; i <= nrOfRemainingMatches; ++i) {
            scanf("%d%d", &teamOne, &teamTwo);

            if(teamOne == nrOfTeams){
                maxScore += 2;
                allGames.emplace_back(teamOne, teamTwo);
            }
            else if (teamTwo == nrOfTeams){
                maxScore += 2;
                allGames.emplace_back(teamOne, teamTwo);
            }
            else {
                gamesLeft.emplace_back(teamOne, teamTwo);
                allGames.emplace_back(teamOne, teamTwo);
            }
        }

        if (nrOfTeams == 1) continue;
        if (scoreOther >= maxScore) {
            cout << "NO" << endl;
            continue;
        }

        Graph graph = Graph();
        for (int i = 0; i < gamesLeft.size() + (nrOfTeams - 1) + 2 ; ++i) graph.addNode(i);

        for (int i = 0; i < gamesLeft.size(); ++i) {
            graph.addEdge(0, i+1, 2);
            pair<int, int> game = gamesLeft[i];
            int tOne = game.first;
            int tTwo = game.second;
            graph.addEdge(i+1, static_cast<int>(tOne + gamesLeft.size()), INT_MAX);
            graph.addEdge(i+1, static_cast<int>(tTwo + gamesLeft.size()), INT_MAX);
        }

        for (int i = 1; i <= nrOfTeams-1; ++i) {
            graph.addEdge(static_cast<int>(gamesLeft.size() + i), static_cast<int>(gamesLeft.size() + nrOfTeams), maxScore - leagueTable[i]-1);
        }

        FordFulkerson fk = FordFulkerson();
        pair<int, vector<Edge> > res = fk.maxFlow(graph, 0, static_cast<int>(gamesLeft.size() + nrOfTeams));

        if(res.first < gamesLeft.size() * 2) cout << "NO";
        else {

            int matches = 0;
            for (int i = 0; i < allGames.size(); ++i) {
                int team1 = allGames[i].first;
                int team2 = allGames[i].second;

                if(team1 == nrOfTeams){
                    cout << 0 << " ";
                }else if(team2 == nrOfTeams){
                    cout << 2 << " ";
                }else{

                    if(res.second[matches].capacity == 1) {
                        cout << 1 << " ";
                        matches++;
                    }
                    else if(res.second[matches].toNode == team1 + gamesLeft.size()) cout << 0 << " ";
                    else if(res.second[matches].toNode == team2 + gamesLeft.size()) cout << 2 << " ";

                    matches++;
                }
            }
        }
        cout << endl;


    }
    return 0;
}