/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 12/2 - 18
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
vector<int> capacities;
struct State{
    State(vector<int> &v, int p){
        cups = v;
        amountPoured = p;
    }
    vector<int> cups;
    int amountPoured;

};

class CompareDist {
public:
    bool operator()(pair<int,State> n1, pair<int,State> n2) {
        return n1.first>n2.first;
    }
};

struct Class1Compare
{
    bool operator() (const State& lhs, const State& rhs) const
    {
        return lhs.cups < rhs.cups;
    }
};

vector<State> findNeighbours(State currState){
    vector<State> neighbours;

    for (int i = 0; i < capacities.size(); ++i) {
        for (int j = 0; j < capacities.size(); ++j) {
            if(i == j) continue;

            int amountToPour = min(currState.cups[i], capacities[j] - currState.cups[j]);
            if(amountToPour == 0) continue;

            State neighbourState = State(currState.cups, amountToPour);
            neighbourState.cups[i] -= amountToPour;
            neighbourState.cups[j] += amountToPour;
            neighbours.push_back(neighbourState);
        }
    }
    return neighbours;
}

class Dijkstras{

public:

    int shortestPath(State &startState, int &goal) {
        map<State, int, Class1Compare> distance;
        priority_queue< pair<int, State>, vector<pair<int, State> >, CompareDist> pq;

        distance.insert(make_pair(startState, 0));
        pq.push(make_pair(distance.at(startState), startState));

        while(!pq.empty()){
            State currState = pq.top().second;
            pq.pop();

            if(currState.cups[0] == goal){
                return distance.at(currState);
            }

            vector<State> neighbours = findNeighbours(currState);

            for(State neighbour : neighbours){

                if(distance.find(neighbour) == distance.end()) {
                    distance.insert(make_pair(neighbour, distance.at(currState) + neighbour.amountPoured));
                    pq.push(make_pair(distance.at(neighbour), neighbour));
                }
                else if(distance.at(neighbour) > distance.at(currState) + neighbour.amountPoured){
                    distance.at(neighbour) = distance.at(currState) + neighbour.amountPoured;
                    pq.push(make_pair(distance.at(neighbour), neighbour));
                }
            }
        }
        return -1;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int nrOfCups;
    scanf("%d", &nrOfCups);


    while(nrOfCups--){
        int cup;
        scanf("%d", &cup);
        capacities.push_back(cup);
    }
    vector<int> initialCups(capacities.size());
    initialCups[0] = capacities[0];
    State initialState = State(initialCups, 0);

    int goal;
    scanf("%d", &goal);

    Dijkstras dk = Dijkstras();
    int res = dk.shortestPath(initialState, goal);

    if(res == -1) cout << "impossible" << endl;
    else cout << res << endl;

    return 0;
}