/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 5/2 - 18
 *
 *  Comments: Algorithm that has been followed to complete this with karatsubas is this:
 *
 *           if n = 1 then return C ← AB
 *           C1 ← A(0)B(0) by a recursive call
 *           C2 ← A(1)B(1) by a recursive call
 *           C3 ← A(0) + A(1)
 *           C4 ← B(0) + B(1)
 *           C5 ← C3C4 by a recursive call
 *           C6 ← C5 − C1 − C2
 *           C ← C1 + C6Xn/2 + C2Xn
 *           return C
 *
 *           With some modifications for speed up.
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
typedef vector<long long int> vi;

vi basicMultiplication(vi X, vi Y)
{
    vi res(X.size()*2);
    // Multiply two polynomials term by term. This is faster than karatsubas when low polynoms.
    for (int i=0; i<X.size(); i++)
    {
        for (int j=0; j<Y.size(); j++)
            res[i+j] += X[i]*Y[j];
    }
    return res;
}

vi karatsuba(vi &X, vi &Y) {
    // Base case, call basic multiplication, faster than karatsubas.
    vi res(X.size()*2);
    if(X.size() < 10){
        return basicMultiplication(X, Y);
    }

    auto halfLength = X.size() / 2;

    // Construct the low, high and middle part.
    vi XLow(static_cast<long long int>(halfLength));
    vi XHigh(static_cast<long long int>(halfLength));
    vi YLow(static_cast<long long int>(halfLength));
    vi YHigh(static_cast<long long int>(halfLength));
    vi C3(static_cast<long long int>(halfLength));
    vi C4(static_cast<long long int>(halfLength));

    for (int i = 0; i < halfLength; ++i) {
        // Split X in two parts, by half.
        XLow[i] = X[i];
        XHigh[i] = X[i + halfLength];

        // Split Y in two parts, by half.
        YLow[i] = Y[i];
        YHigh[i] = Y[i + halfLength];

        // According to algorithm, construct C3 and C4 by add every term in splitted XLow and XHigh.
        C3[i] = XLow[i] + XHigh[i];
        C4[i] = YLow[i] + YHigh[i];
    }

    vi C1 = karatsuba(XLow, YLow);
    vi C2 = karatsuba(XHigh, YHigh);
    vi C5 = karatsuba(C3, C4);

    // Append the results from each part.
    // C1, which is the lower part
    // C2, which is the upper part
    // C6 = C5[i] - C1[i] - C2[i], which is the middle part is be placing on the middle.
    // This is the "trick" in karatsubas.
    for (long long int i = 0 ; i < X.size(); ++i) {
        res[i] += C1[i];
        res[i + X.size()] += C2[i];
        res[i + halfLength] += C5[i] - C1[i] - C2[i];
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    int testCases;
    scanf ("%d",&testCases);
    long long int degreeX, degreeY;
    long long int xTmp, yTmp;

    while (testCases--) {
        vi X;
        vi Y;
        // Read all the values in the first polynom.
        scanf ("%lld",&degreeX);
        for (int i = 0; i <= degreeX; ++i) {
            scanf ("%lld",&xTmp);
            X.push_back(xTmp);
        }

        // Read all the values in the second polynom.
        scanf ("%lld",&degreeY);
        for (int i = 0; i <= degreeY; ++i) {
            scanf ("%lld",&yTmp);
            Y.push_back(yTmp);
        }

        // Make sure both polynom X and Y are equal length.
        auto maxLength = max(degreeX, degreeY);
        for (long int i = degreeX; i < maxLength; ++i) X.push_back(0);
        for (long int i = degreeY; i < maxLength; ++i) Y.push_back(0);

        // Make sure the size of polynom X and Y is a power of 2, i.e 1,2,4,8,16 and so on.
        // This is because we are splitting the vectors in half in Karatsuba.
        while (true) {
            if ((X.size() & (X.size() - 1)) == 0) break;
            X.push_back(0);
            Y.push_back(0);
        }

        // Karatsuba algorithm.
        vi answer = karatsuba(X, Y);


        // Need to remove the unecessary zeros at the end.
        auto nrOfZeros = 0;
        for (auto i = static_cast<long long int>(answer.size() - 1); i >= 0; --i) {
            if(answer[i] != 0) break;
            nrOfZeros++;
        }

        // Print the answer.
        printf("%ld\n", answer.size() - nrOfZeros - 1);
        for (int j = 0; j < answer.size() - nrOfZeros; ++j) {
            printf("%lld ", answer[j]);
        }
        printf("\n");
    }
    return 0;
}