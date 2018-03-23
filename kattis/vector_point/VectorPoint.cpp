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

# define M_PI 3.14159265358979323846  /* pi */

using namespace std;
typedef vector<int> vi;
typedef double type;

struct Point{
    Point(type a, type b) : x(a), y(b) {}
    type x;
    type y;
};

struct Vector{
    Vector(Point A, Point B) : vec(make_pair(B.x - A.x, B.y - A.y)){}
    pair<type, type> vec;
};

struct PointClass{

    type length(Vector v){
        type a = v.vec.first;
        type b = v.vec.second;
        return sqrt(a*a + b*b);
    }

    type scalar(Vector v1, Vector v2){
        type a = v1.vec.first * v2.vec.first;
        type b = v1.vec.second * v2.vec.second;
        return a+b;
    }

    type angle(Vector v1, Vector v2){
        type sc = scalar(v1, v2);
        type l1 = length(v1);
        type l2 = length(v2);
        type l  = l1*l2;
        type r = sc/l;
        return acos(r) * 180.0 / M_PI;
    }
};

int main() {

    PointClass pc = PointClass();

    Point A = Point(0 , 0);
    Point B = Point(1 , 1);
    Vector v1 = Vector(A, B);

    A = Point(0, 0);
    B = Point(1, -1);
    Vector v2 = Vector(A, B);

 //   cout << pc.length(v1) << endl;
  //  cout << pc.length(v2) << endl;
  //  cout << pc.scalar(v1, v2) << endl;
  //  cout << pc.angle(v1,v2) << endl;


    return 0;
}