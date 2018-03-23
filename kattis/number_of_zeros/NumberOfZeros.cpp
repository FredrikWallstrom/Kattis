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

long long int calcZeros(long long int number){
    long long int res = 1;
    long long int stepper = 1;

    while(true){
        // Take out current digit, starting from the back of the number.
        auto tmp = static_cast<long long int>(floor(number / stepper));
        long long int currentDigit = tmp % 10;

        // Cut the number in two halves, remaining number and processed number.
        long long int processedNumber = number % stepper;
        auto remainingNumber = static_cast<long long int>(floor(tmp / 10));

        // There is no more numbers left, we are done.
        if(processedNumber == number) break;

        if(currentDigit == 0){
            // CurrentDigit is zero, there is a special case.
            // Ex if the number is 907
            // ?0? we got we got 9 ways to choose the hundreds.
            // For 1,2,3 ... , 8 we can choose any last digit (stepper) so, 8 * stepper.
            // For the 9 we can only choose a number between 0 and 7
            // 0 and 7 is represented as processedNumer (7) and + 1 for the 0.
            res += (remainingNumber - 1) * stepper + processedNumber + 1;
        }else{
            // CurrentDigit is not zero, there are remainingNumber possibilities for a zero on the left
            // and stepper possibilities for a zeros on the right of CurrentDigit.
            // Ex if the number is 999
            // ??9 we got 99 remaining numbers and stepper 1
            // ?9? we got 9 remaining numbers and stepper 10
            // 9?? we got 0 remaining numbers and stepper 100
            res += remainingNumber * stepper;
        }
        stepper *= 10;
    }
    return res;

}

int main() {
    while(true){
        long long int lower, upper;
        cin >> lower >> upper;

        if(lower == -1 && upper == -1) break;

        long long int lowerBound = 0;
        if(lower != 0){
            lowerBound = calcZeros(lower-1);
        }
        long long int upperBound = calcZeros(upper);
        cout << upperBound - lowerBound << endl;

    }
    return 0;
}