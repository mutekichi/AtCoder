#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <bitset>
#include <utility>
#include <complex>
#include <climits>
#include <cfloat>
#include <ctime>
#include <cstdlib>

using namespace std;

const double PI = 3.14159265358979323846;

struct Point {
    double x, y;
};

Point operator-(Point &x, Point &y) {
    return Point{x.x - y.x, x.y - y.y};
}

double get_angle(Point &p1, Point &p2, Point &p_center) {
    Point v1 = p1 - p_center;
    Point v2 = p2 - p_center;

    double dot = v1.x * v2.x + v1.y * v2.y;

    double cos = dot / (sqrt(v1.x * v1.x + v1.y * v1.y) * sqrt(v2.x * v2.x + v2.y * v2.y));
    double rad = acos(cos) * 180 / PI;
}

double get_max_angle(vector<Point> &points, int center_index) {
    
}

int main() {

    int n;

    cin >> n;

    vector<Point> points(n);

    for (int i = 0; i < n; ++i) {
        Point p;
        cin >> p.x >> p.y;
        points[i] = p;
    }

    for (int i = 0; i < n; ++i) {

    }


    
    return 0;
}