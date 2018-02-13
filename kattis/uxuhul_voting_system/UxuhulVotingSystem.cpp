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

using namespace std;

// This list tells us how many flips we need from given outcome to another.
int flipCounter[8][8] =  {{0, 1, 1, 2, 1, 2, 2, 3}, {1, 0, 2, 1, 2, 1, 3, 2}, {1, 2, 0, 1, 2, 3, 1, 2}, {2, 1, 1, 0, 3, 2, 2, 1},
                   {1, 2, 2, 3, 0, 1, 1, 2}, {2, 1, 3, 2, 1, 0, 2, 1}, {2, 3, 1, 2, 1, 2, 0, 1}, {3, 2, 2, 1, 2, 1, 1, 0}};

void print(int p){
    if(p == 0) cout << "NNN" << endl;
    if(p == 1) cout << "NNY" << endl;
    if(p == 2) cout << "NYN" << endl;
    if(p == 3) cout << "NYY" << endl;
    if(p == 4) cout << "YNN" << endl;
    if(p == 5) cout << "YNY" << endl;
    if(p == 6) cout << "YYN" << endl;
    if(p == 7) cout << "YYY" << endl;
}

int main() {

    int nrTestCases, nrOfVotingPriests, preference;
    cin >> nrTestCases;

    while(nrTestCases--){
        cin >> nrOfVotingPriests;

        int preferences[nrOfVotingPriests][8];

        // Initialize preferences with the same as input.
        for (int row = 0; row < nrOfVotingPriests; ++row) {
            for (int col = 0; col < 8; ++col) {
                cin >> preference;
                preferences[row][col] = preference;
            }
        }

        int result[nrOfVotingPriests][8];

        // Fill result from last priest to first priest.
        // Go through all priests, starting backwards.
        for (int priest = nrOfVotingPriests - 1; priest >= 0; --priest) {
            // Go through all possible outComes.
            for (int outCome = 0; outCome < 8; ++outCome) {
                int bestOutcome = -1;
                int bestPref = 10;
                int currPref = 10;
                int currInsideOutcome = -1;
                // Go through the outcome "inside" one outcome, check the flip counter array.
                for (int insideOutcome = 0; insideOutcome < 8; ++insideOutcome) {

                    // If we are the last priest we cant access priest + 1.
                    // The last priest can flip if the "flip counter" is 1.
                    // Take out currentPreference for the last priest.
                    // Save the insideOutcome if the preference is the best.
                    if(priest == nrOfVotingPriests - 1){
                        if(flipCounter[outCome][insideOutcome] == 1){
                            currPref = preferences[priest][insideOutcome];
                            currInsideOutcome = insideOutcome;
                        }

                    // If we not are on the last priest, we check which outCome we can flip to.
                    // The current priest can flip if the "flip counter" is 1.
                    // Take out currentPreference for that priest, here we need to check in DP table for the priest "before".
                    // Save the insideOutcome if the preference is the best, which is given from priest "before".
                    } else{
                        if(flipCounter[outCome][insideOutcome] == 1) {
                            currPref = preferences[priest][result[priest + 1][insideOutcome]];
                            currInsideOutcome = result[priest + 1][insideOutcome];
                        }
                    }

                    if (currPref < bestPref) {
                        bestOutcome = currInsideOutcome;
                        bestPref = currPref;
                    }

                }
                // Set the result.
                result[priest][outCome] = bestOutcome;
            }
        }
        print(result[0][0]);
    }
    return 0;
}