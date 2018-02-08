/* -*- Mode: C++ -*- */

/**
 *  Author: Fredrik Wallström
 *  Date: 8/2 - 18
 *
 *  Comments: This is used when we are solving something that is involving weight on some way, and different objects.
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

struct object{
    int weight;
    int value;
};

int matrix[2002][2002];
int numberOfObjects;

vi knapsack(int capacity, object objects[]){

    // Padd the first row with zeros.
    for (int col = 0; col <= capacity; ++col) {
        matrix[0][col] = 0;
    }

    // Padd the first column with zeros.
    for (int row = 0; row <= numberOfObjects; ++row) {
        matrix[row][0] = 0;
    }

    // Fill the matrix, idea:
    // If current column is less than current object, place the value matrix[row-1][col] at current value.
    // Which means the best value we can get has not changed.
    // If not, we check which the best value we can get by taking max of current best value or,
    // the value we will get by take the current value + the value that is left one row above when we had subtract
    // the current weight.
    for (int row = 1; row <= numberOfObjects; ++row) {
        for (int col = 1; col <= capacity; ++col) {
            if(col < objects[row].weight) matrix[row][col] = matrix[row-1][col];
            else matrix[row][col] = max(objects[row].value + matrix[row-1][col-objects[row].weight],
                                       matrix[row-1][col]);
        }

    }
    // Restore the result
    int row = numberOfObjects;
    int col = capacity;
    vi indexes;

    // Start att the bottom right corner in the matrix.
    // When we arrive at container with 0, we are done.
    // The steps are:
    // 1. If current value in matrix is the same as above. Current value cant be an answer. Go up one row.
    // 2. If not one, go back currents weight in columns, and one step up in rows, and add the index to result.
    while(matrix[row][col] != 0){
        if(matrix[row][col] == matrix[row-1][col]) row--;
        else if(matrix[row][col] != matrix[row-1][col]){
            col -= objects[row].weight;
            row --;
            indexes.push_back(row);
        }
    }
    return indexes;
}

int main() {
    double c;
    while(cin >> c >> numberOfObjects){
        // Store value and weight as an struct object, this is how many objects we have.
        object objects[numberOfObjects];
        auto capacity = static_cast<int>(floor(c));

        // Read all objects.
        for (int i = 1; i <= numberOfObjects; ++i) {
            object o;
            int value;
            int weight;
            cin >> value;
            cin >> weight;
            o.weight = weight;
            o.value = value;
            objects[i] = o;
        }

        vi indexes = knapsack(capacity, objects);


        // Print the indexes.
        cout << indexes.size() << endl;
        for (long int i = indexes.size()-1; i >= 0; --i) {
            cout << indexes[i] << " ";
        }
        cout << endl;

    }
    return 0;
}