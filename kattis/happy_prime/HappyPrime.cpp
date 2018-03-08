/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 8/3 - 18
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

bool isPrime(int &primeCandidate){

    if(primeCandidate == 1){
        return false;
    }

    if(primeCandidate == 2){
        return true;
    }

    if(primeCandidate % 2 == 0){
        return false;
    }

    for (int i = 3; i <= sqrt(primeCandidate); i += 2) {
        if(primeCandidate % i == 0){
            return false;
        }
    }

    return true;
}

int getNumberOfDigits (int number)
{
    int nrOfDigits = 0;

    while(number > 0) {
        number = number / 10;
        nrOfDigits++;
    }
    return nrOfDigits;
}

bool isHappy(int happyCandidate){

    set<int> sums;
    while(true) {
        int sum = 0;

        for (int i = 0; i < getNumberOfDigits(happyCandidate); ++i) {
            stringstream tmp;
            tmp << happyCandidate;
            char currCharDigit = (tmp.str())[i];
            int currDigit = currCharDigit - '0';
            sum += (currDigit * currDigit);
        }

        // Happy
        if(sum == 1){
            return true;
        }
        // A number is not happy if the sum is appeared before.
        else if(sums.find(sum) != sums.end()){
            return false;
        }

        sums.insert(sum);
        happyCandidate = sum;
    }
}

int main() {
    int nrOfTestCases;
    cin >> nrOfTestCases;

    while(nrOfTestCases--){
        int testCase = 0, happyPrimeCandidate;
        cin >> testCase >> happyPrimeCandidate;

        cout << testCase << " " << happyPrimeCandidate << " ";
        if(isPrime(happyPrimeCandidate) && isHappy(happyPrimeCandidate)){
            cout << "YES";
        }else{
            cout << "NO";
        }
        cout << endl;
    }

    return 0;
}