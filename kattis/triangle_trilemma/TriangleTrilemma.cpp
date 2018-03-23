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

    double calcTriangleArea(double a, double b, double c){
        double s = (a + b + c) / 2.0;
        return sqrt(s*(s-a)*(s-b)*(s-c));
    }

    void flipVector(Vector &v){
        v.vec.first *= -1;
        v.vec.second *= -1;
    }
};

int main() {

    int nrOfTestCases;
    cin >> nrOfTestCases;
    int counter = 1;

    while(nrOfTestCases--){
        string res = "Case #" + to_string(counter++) + ": ";
        int x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

        Point A = Point(x1, y1);
        Point B = Point(x2, y2);
        Point C = Point(x3, y3);

        Vector v1 = Vector(A, B);
        Vector v2 = Vector(A, C);
        Vector v3 = Vector(B, C);
        Vector v4 = Vector(C, B);

        PointClass pc = PointClass();
        double area = pc.calcTriangleArea(pc.length(v1), pc.length(v2), pc.length(v3));
        // Precision problem of doubles.
        if(area <= 0.01){
            res.append("not a triangle");
            cout << res << endl;
            continue;
        }

        if(pc.length(v1) == pc.length(v2) || pc.length(v1) == pc.length(v3) || pc.length(v2) == pc.length(v3)){
            res.append("isosceles ");
        }else{
            res.append("scalene ");
        }

        if(pc.angle(v1, v2) == 90 || pc.angle(v1, v4) == 90 || pc.angle(v2, v3) == 90){
            res.append("right triangle");
        }else if(pc.angle(v1, v2) > 90 || pc.angle(v1, v4) > 90 || pc.angle(v2, v3) > 90){
            res.append("obtuse triangle");
        }else{
            res.append("acute triangle");
        }

        cout << res << endl;
    }

    return 0;
}