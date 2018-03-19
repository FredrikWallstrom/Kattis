/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date:
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
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <bitset>


using namespace std;

template <size_t N>
bool sat(vector<string> &clause, bitset<N> &bs){
    for (auto literal : clause) {
        // Negation.
        if(literal[0] == '~'){
            string stringIndex;
            for (int j = 2; j < literal.size(); ++j) {
                stringIndex += literal[j];
            }
            int index = stoi(stringIndex);
            index--;
            if(bs[index] == 0) return true;
        }
        // Not negation.
        else{
            string stringIndex;
            for (int j = 1; j < literal.size(); ++j) {
                stringIndex += literal[j];
            }
            int index = stoi(stringIndex);
            index--;
            if(bs[index] == 1) return true;
        }

    }
    return false;
}

/*
 * This will work as follows:
 * we start with 000 for example.
 * The we going to flip the first so we get 001 and check if requested bit is set. it will return true and break
 * Next time we will flip 001 to 000 and check if first bit is set. it wont be set so take next.
 * It will flip from 000 to 010 and check if bit two is set, it will return true and break.
 * This will generate:
 * 000
 * 001
 * 010
 * 011
 * 100
 * 101
 * 110
 * 111
 * Exactly as we want!!!
 */

template <size_t N>
void incrementBitset(bitset<N> &bs)
{
    for (size_t i = 0; i != bs.size(); ++i) {
        if (bs.flip(i).test(i)) {
            break;
        }
    }
}

int main() {
    int nrOfTestCases;
    cin >> nrOfTestCases;

    while(nrOfTestCases--){
        int nrOfVariables, nrOfClauses;
        cin >> nrOfVariables >> nrOfClauses;

        // Read all clauses
        cin.ignore();
        vector<vector<string> > clauses;
        string literals;
        for (int i = 0; i < nrOfClauses; ++i) {
            getline(cin, literals);
            istringstream iss(literals);
            vector<string> clause;
            for (string s; iss >> s;) {
                if(s != "v") clause.push_back(s);
            }
            clauses.push_back(clause);
        }


        // Main loop, Try all different assignments on the SAT-problem
        // and se if we can satisfy all clauses.
        // Else increase the assignment to next and try.
        // For that we use bitset.
        bitset<20> bs(0);
        bool firstRun = true;
        bool satisfiable = true;
        for (int i = 0; i < pow(2, nrOfVariables); ++i) {
            if(!firstRun){
                incrementBitset(bs);
            }
            satisfiable = true;
            for (auto &clause : clauses) {
                if(!sat(clause, bs)){
                    satisfiable = false;
                    break;
                }
            }
            if(satisfiable) break;
            firstRun = false;
        }

        if(satisfiable) cout << "satisfiable" << endl;
        else cout << "unsatisfiable" << endl;

    }

    return 0;
}