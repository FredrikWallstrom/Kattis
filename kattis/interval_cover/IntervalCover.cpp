/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 20/1 -18
 *
 *  Comments: Checks how many intervals we least need to cover an given interval.
 *
 *  Lessons Learned: Be aware of edge cases! In this case I didn't check when target interval is only a peak.
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
typedef pair<double, double> pd;
typedef vector<pd> vp;

/**
 * Help function that translates the the sorted index to the correct original index.
 */
int translateIndex(pd p, vp intervals)
{
    for (int i = 0; i < intervals.size(); ++i)
    {
        if(intervals[i] == p) return i;
    }
    return -1;
}

/**
 * Help function to detect if a peak can be covered with the intervals.
 */
int peakCover(vp intervals, double peak){
    for (int i = 0; i < intervals.size(); ++i)
    {
        if(intervals[i].first <= peak && peak <= intervals[i].second) return i;
    }
    return -1;
}

/**
 * Method used to detect if the intervals can cover the target interval.
 * @return: The indexes of the intervals we need to cover the target interval with.
 */
vi cover(pd targetInterval, vp intervals)
{
    vi res;
    double upperBound = targetInterval.second;
    double lowerBound = targetInterval.first;
    double currentLowerBound = lowerBound;
    int startIndex = 0;

    // If lower bound equals to upper bound, we need to check if intervals cover the peak.
    // Edge case.
    if(lowerBound == upperBound){
        int peak = peakCover(intervals, lowerBound);
        if(peak != -1) res.push_back(peak);
        return res;
    }

    // Store the original intervals in tmp, so we can get the original index back.
    vp tmpIntervals = intervals;
    sort(intervals.begin(), intervals.end());

    while(lowerBound < upperBound)
    {
        int indexOfInterval = -1;
        for (int i = startIndex; i < intervals.size(); ++i)
        {
            pd tmp = intervals[i];
            if(tmp.first <= lowerBound){
                if(tmp.second > currentLowerBound){
                    currentLowerBound = tmp.second;
                    indexOfInterval = i;
                }
            }else{
                startIndex = i;
                break;
            }
        }

        // Check if we found a interval that can cover.
        // Else clear the vector we have started to build and return.
        if(indexOfInterval != -1){
            lowerBound = currentLowerBound;
            int tmpIndex = translateIndex(intervals[indexOfInterval], tmpIntervals);
            if(tmpIndex != -1) res.push_back(tmpIndex);
        }else{
            res.clear();
            break;
        }
    }

    return res;
}

/**
 * Read the given information
 * @return: The indexes needed to fill the target interval.
 */
int main()
{
    double lowerBound, upperBound;
    int nrIntervals;

    while(cin >> lowerBound >> upperBound)
    {

        pd targetInterval = make_pair(lowerBound, upperBound);
        cin >> nrIntervals;

        vp intervals;
        for (int i = 0; i < nrIntervals; ++i)
        {
            cin >> lowerBound >> upperBound;
            pd tmpPair = make_pair(lowerBound, upperBound);
            intervals.push_back(tmpPair);
        }

        vi res = cover(targetInterval, intervals);

        if(res.empty()) cout << "impossible" << endl;
        else{
            cout << res.size() << endl;
            for (int re : res) {
                cout << re << " ";
            }
            cout << endl;
        }
    }
    return 0;
}

