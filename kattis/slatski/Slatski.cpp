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

int main() {

    long long int price, smallestBillZero;

    cin >> price;
    cin >> smallestBillZero;

    long long int startingPrice = price;



    long long int smallestBill = 1;
    for (int i = 0; i < smallestBillZero; ++i) {
       smallestBill *= 10;
    }


    long long int res = 0;
    while(true){
        if(price-smallestBill > 0) {
            res+= smallestBill;
            price -= smallestBill;
        }
        else break;
    }


    long long int over = res+smallestBill;
    if(over-startingPrice <= startingPrice-res){
        cout << over;
    }else{
        cout << res;
    }


    return 0;
}