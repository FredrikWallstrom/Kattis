/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 3/3 - 18
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

struct Kmp{

    /**
     * Build a prefix table that is used so we can speed up the search for prefix match in the KMP algorithm.
     * Pattern “AAACAAAAAC” will have table [0, 1, 2, 0, 1, 2, 3, 3, 3, 4].
     * pos is the current position in the pattern.
     * len is the current length of the current prefix match.
     */
    void computeKmpTable(string &pattern, vector<int> &table){
        int pos = 1;
        int len = 0;
        table[0] = 0;

        while(pos < pattern.size()){

            if(pattern[pos] == pattern[len]){
                len++;
                table[pos] = len;
                pos++;
            }else{
                if (len != 0) len = table[len-1];
                else table[pos] = 0, pos++;
            }
        }
    }

    /**
     *    Standard KMP algorithm.
     *    Idea is to "slide" the pattern over the string and check for matches, but don't on the naivé way.
     *    If we cant get a match at the first char in pattern, we will just increase on tha naive way with one.
     *    If we cant match a char in the middle of a pattern we can skip some chars, this is done via the KMPTable.
     *
     *    EX:
     *    String: ABC ABCDAB ABCDABCDABDE
     *    Patt:   ABCDABD
     *
     *    Here we can match ABC, but not the D so here we can skip ABC for next search like this:
     *
     *    String: ABC ABCDAB ABCDABCDABDE
     *    Patt:      ABCDABD
     */
    vector<int> find(string &pattern, string &text){
        // Compute KmpTable for KMP algorithm.
        vector<int> table(pattern.size());
        computeKmpTable(pattern, table);

        vector<int> res;
        int textIndex = 0;
        int patternIndex = 0;

        while(textIndex < text.size()){
            // If we got a char match, increase the indexes.
            if(pattern[patternIndex] == text[textIndex]) {
                textIndex++;
                patternIndex++;
            }
            // We got a whole match!
            // We don't need to start over the match, the value in table gives the starting index we need to match next.
            if(patternIndex == pattern.size()) {
                res.push_back(textIndex - patternIndex);
                patternIndex = table[patternIndex - 1];
            }
            // We got a missmatch, move the patternIndex backward. If it is zero already, step one with textIndex.
            else if(textIndex < text.size() && pattern[patternIndex] != text[textIndex]){
                if (patternIndex != 0) patternIndex = table[patternIndex-1];
                else textIndex++;
            }
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    string pattern, text;

    while(getline(cin, pattern)){
        getline(cin, text);

        Kmp kmp = Kmp();
        vector<int> res = kmp.find(pattern, text);

        for (int r : res) cout << r << " ";
        cout << endl;
    }
    return 0;
}