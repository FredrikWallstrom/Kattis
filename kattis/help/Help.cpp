/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 24/1 -18
 *
 *  Comments: This problem is to match two patterns, like,
 *          how now brown <animal>
 *          <foo> now <color> cow
 *
 *          Here the resulting string should be:
 *          how now brown cow
 *
 *          Just change <foo> to how, <color> to brown and <animal> to cow.
 *
 *          You could have like:
 *          <animal> <animal> cow <animal> <cat>
 *          <cat> <hej> <hej> <animal> <cat>
 *
 *          Which will make it little more tricky.
 *
 *  Lessons Learned: Think about if the first solution is really working or not.
 *                   Try some more "harder" test examples or something to see if it the suggested solution work!
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
typedef vector<int> vi;
typedef vector<string> vs;

void replaceAll(vs &vector, string oldValue, string newValue){
    for (auto &i : vector) {
        if(i == oldValue) {
            i = newValue;
        }
    }
}

int main() {
    int nrTestCases;

    cin >> nrTestCases;
    cin.ignore();

    while(nrTestCases--){

        // Read the first line, save it in vector.
        string s;
        vs firstLine;
        string line;
        getline(cin, line);
        istringstream iss(line);
        while (getline(iss, s, ' ') ) {
            firstLine.push_back(s);
        }

        // Read the second line, save it in vector.
        string s2;
        vs secondLine;
        string line2;
        getline(cin, line2);
        istringstream iss2(line2);
        while (getline(iss2, s2, ' ') ) {
            secondLine.push_back(s2);
        }

        if(firstLine.size() != secondLine.size()){
            cout << "-" << endl;
            continue;
        }

        restart:
        // Go through vector, check if we can choose some <value>.
        // Restart when we had change every value in the vector.
        for (int i = 0; i < firstLine.size(); ++i) {

            if(firstLine[i].at(0) == '<' && secondLine[i].at(0) != '<'){
                // Change all values in first line to the value in the second line.
                replaceAll(firstLine, firstLine[i], secondLine[i]);
                goto restart;
            }
            else if(firstLine[i].at(0) != '<' && secondLine[i].at(0) == '<'){
                // Change all values in second line to the value in the first line.
                replaceAll(secondLine, secondLine[i], firstLine[i]);
                goto restart;
            }

        }

        // This case is for when we got a value that is the same, that is not set yet,
        // like <value> <value> for both first and second pattern.
        // Restart if so is the case, to set all other values to that.
        for (int j = 0; j < firstLine.size(); ++j) {
            if(firstLine[j].at(0) == '<' && firstLine[j].at(0) == '<'){
                // Change all values in first line to "whatever".
                replaceAll(firstLine, firstLine[j], "whatever");
                // Change all values in second line to "whatever".
                replaceAll(secondLine, secondLine[j], "whatever");

                goto restart;
            }
        }

        // Compare the vectors and see if match.
        if(firstLine == secondLine){
            for (const auto &i : secondLine) {
                cout << i << " ";
            }
            cout << endl;

        }else cout << "-" << endl;

    }
    return 0;
}