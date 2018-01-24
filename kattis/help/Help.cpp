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
typedef vector<int> vi;
typedef vector<string> vs;

int main() {
    int nrTestCases;

    cin >> nrTestCases;
    cin.ignore();

    while(nrTestCases--){

        string s;
        vs firstLine;
        string line;
        getline(cin, line);
        istringstream iss(line);
        while (getline(iss, s, ' ') ) {
            firstLine.push_back(s);
        }

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

        map<string, string> v2;
        map<string, string> v1;

        unsigned long loop_size = firstLine.size();
        string result[loop_size];

        bool breaked = false;

        for (int j = 0; j < loop_size; ++j) {
            if (firstLine[j].at(0) != '<' && secondLine[j].at(0) != '<') {
                if (firstLine[j] == secondLine[j]) {
                    result[j] = firstLine[j];
                    continue;
                } else {
                    breaked = true;
                    break;
                }
            } else if (firstLine[j].at(0) != '<' && secondLine[j].at(0) == '<') {
                map<string, string>::iterator it;
                it = v2.find(secondLine[j]);
                if (it != v2.end()) {
                    // Found
                    if (v2.at(secondLine[j]) == firstLine[j]) {
                        result[j] = firstLine[j];
                        continue;
                    } else {
                        breaked = true;
                        break;
                    }
                } else {
                    // Not found
                    v2[secondLine[j]] = firstLine[j];
                    result[j] = firstLine[j];
                    continue;
                }
            } else if (firstLine[j].at(0) == '<' && secondLine[j].at(0) != '<') {

                map<string, string>::iterator it;
                it = v1.find(firstLine[j]);
                if (it != v1.end()) {
                    // Found
                    if (v1.at(firstLine[j]) == secondLine[j]) {
                        result[j] = secondLine[j];
                        continue;
                    } else {
                        breaked = true;
                        break;
                    }
                } else {
                    // Not found
                    v1[firstLine[j]] = secondLine[j];
                    result[j] = secondLine[j];
                    continue;
                }
            }
        }

        if(breaked) {
            cout << "-" << endl;
            continue;
        }

        for (int i = 0; i < loop_size; ++i) {
            if(firstLine[i].at(0) == '<' && secondLine[i].at(0) == '<') {
                map<string, string>::iterator it1;
                it1 = v1.find(firstLine[i]);

                map<string, string>::iterator it2;
                it2 = v2.find(secondLine[i]);

                if (it1 != v1.end() && it2 != v2.end()) {
                    if(it1->second == it2->second) {
                        result[i] = it1->second;
                        continue;
                    }else{
                        breaked = true;
                        break;
                    }
                }
                else if (it1 != v1.end() && it2 == v2.end()) {
                    result[i] = it1->second;
                    v2[secondLine[i]] = it1->second;
                    continue;
                }
                else if (it1 == v1.end() && it2 != v2.end()) {
                    result[i] = it2->second;
                    v1[firstLine[i]] = it2->second;
                    continue;
                }
            }
        }

        if(breaked) {
            cout << "-" << endl;
            continue;
        }

        for (int l = 0; l < loop_size; ++l) {
            if(firstLine[i].at(0) == '<' && secondLine[i].at(0) == '<') {


            }
        }

        for (int k = 0; k < loop_size; ++k) {
            cout << result[k] << " ";
        }
        cout << endl;
    }
    return 0;
}