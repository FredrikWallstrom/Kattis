/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 20/1 -18
 *
 *  Comments: Program that calculates the anger of the child.
 *              The anger is the candys^2 they missing.
 *
 *  Lessons Learned: Be aware and try to optimize the program os good as possible.
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

/**
 * Calculates the anger by first assume every child got their wishes.
 * Then we calculates the average candys we need to remove of every child.
 * If we sort the childs wishes we can just check if the lowest child wishes is lower than the average.
 * If so we can just remove from that first person, else we can remove the average from everyone.
 */
unsigned long long int
calculateAnger(unsigned long long int nrChild,
               unsigned long long int candysToGive,
               unsigned long long int originalChilds[],
               unsigned long long int totalCandys) {


    sort(originalChilds, originalChilds + nrChild);
    unsigned long long int tmpChilds[nrChild];
    copy(originalChilds, originalChilds + nrChild, tmpChilds);
    unsigned long long int currentIndex = 0;

    while (true) {
        unsigned long long int childToRemove = 0;
        unsigned long long int candyToRemoveAverage = (totalCandys - candysToGive) / (nrChild - currentIndex);

        if (candyToRemoveAverage < tmpChilds[currentIndex]) {
            for (unsigned long long int i = currentIndex; i < nrChild; ++i) {
                tmpChilds[i] = tmpChilds[i] - candyToRemoveAverage;
                totalCandys -= candyToRemoveAverage;
                if (tmpChilds[i] == 0) childToRemove++;
            }
            currentIndex += childToRemove;
            break;
        } else {
            totalCandys -= tmpChilds[currentIndex];
            tmpChilds[currentIndex] = 0;
            currentIndex++;
        }

    }

    // This loop is needed if the average is not a integer, i.e an float.
    // Than we need to go through and remove one single candy until total candys == candys we have to give.
    if (candysToGive < totalCandys) {
        for (unsigned long long int i = currentIndex; i < nrChild; ++i) {
            tmpChilds[i]--;
            totalCandys--;
            if (candysToGive == totalCandys) break;
        }
    }

    unsigned long long int anger = 0;
    for (unsigned long long int j = 0; j < nrChild; ++j) {
        anger += (originalChilds[j] - tmpChilds[j]) * (originalChilds[j] - tmpChilds[j]);
    }
    return anger;
}

/**
 * Read all input data.
 * @return: The sum of anger of all childs.
 */
int main() {
    unsigned long long int candysToGive;
    unsigned long long int nrChild;
    scanf("%llu", &candysToGive);
    scanf("%llu", &nrChild);

    unsigned long long int originalChilds[nrChild];
    unsigned long long int child;
    unsigned long long int totalCandys = 0;

    for (int i = 0; i < nrChild; ++i) {
        scanf("%llu", &child);
        originalChilds[i] = child;
        totalCandys += child;
    }
    unsigned long long int anger = calculateAnger(nrChild, candysToGive, originalChilds, totalCandys);

    printf("%llu", anger);
    return 0;
}
