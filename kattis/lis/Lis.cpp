/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 26/1 -18
 *
 *  Comments: Exercise is to build the longest increasing subsequence of given sequence.
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

/**
 * Binary search that will return the index of the element we want to change in the lastElem.
 */
int binarySearch(int i, vector<int> &lastElem, vector<int> &sequence, int length){
    int start = 0;
    int end  = length-1;
    while (start < end){
        int mid = (start + end) / 2;
        if(sequence[lastElem[mid]] < sequence[i]){
            start = mid + 1;
        }else{
            end = mid;
        }
    }
    return start;
}

/**
 * The idea is to o through the list of sequence, one element at the time, and build a new list.
 * We can place the new element in the list at the beginning, in the middle somewhere or at the end.
 * It depends on the new element is lower than the first element, between first element and last element or
 * higher than the last element.
 * We need to keep track of indexes of previous elements when we insert something in the new list to
 * reconstruct the list at the end.
 */
vector<int> lis(vector<int> sequence) {
    vector<int> previous(sequence.size(), -1);
    vector<int> lastElem(sequence.size(), 0);
    int seqLength = 1;


    for (int i = 1; i < sequence.size(); ++i) {
        // Place the current element in the first place in the builded list.
        if(sequence[i] < sequence[lastElem[0]]){
            lastElem[0] = i;
        }

        // Place the current element in the last place in the builded list.
        else if(sequence[i] > sequence[lastElem[seqLength-1]]){
            previous[i] = lastElem[seqLength-1];
            lastElem[seqLength] = i;
            seqLength++;
        }

        // Replace Index with the current element, since current element fits somewhere in the list.
        // Index is given from binary search.
        else{
            int index = binarySearch(i, lastElem, sequence, seqLength);
            previous[i] = lastElem[index - 1];
            lastElem[index] = i;
            if(index > seqLength){
                seqLength++;
            }
        }
    }
    // Reconstruct the list.
    vector<int> res(seqLength);
    int index = lastElem[seqLength-1];
    for (int j = seqLength-1; j >= 0; j--) {
        res[j] = index;
        index = previous[index];
    }
    return res;
}


int main() {
    int testCases;
    while(scanf("%d", &testCases) == 1){
        // Read the sequence.
        int value;
        vector<int> sequence;
        while(testCases--){
            scanf("%d", &value);
            sequence.push_back(value);
        }
        vector<int> res = lis(sequence);

        // Print the result
        printf("%d\n", res.size());
        for (int re : res) {
            printf("%d ", re);
        }
        printf("\n");
    }
    return 0;
}