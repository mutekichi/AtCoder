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

class PointSet {
public:
    PointSet() {}

    PointSet(vector<pair<long long, long long>> &points) {
        this->points = points;
    }

    void add_point(pair<long long, long long> &point) {
        points.push_back(point);
    }

    void add_points(vector<pair<long long, long long>> &points) {
        this->points.insert(this->points.end(), points.begin(), points.end());
    }

    /**
     * @brief Get the convex hull object
     * 
     * @return vector<pair<long long, long long>>
     * 
     * @note 0th point is the leftmost point of the convex hull and the points are sorted in counterclockwise order.
     */
    vector<pair<long long, long long>> get_convex_hull() {
        vector<pair<long long, long long>> convex_hull;
        if (points.size() <= 2) {
            convex_hull = points;
            return convex_hull;
        }

        sort(points.begin(), points.end());
        vector<pair<long long, long long>> upper_hull;
        for (int i = 0; i < points.size(); ++i) {
            while (upper_hull.size() >= 2 && ccw(upper_hull[upper_hull.size() - 2], upper_hull[upper_hull.size() - 1], points[i]) <= 0) {
                upper_hull.pop_back();
            }
            upper_hull.push_back(points[i]);
        }

        vector<pair<long long, long long>> lower_hull;
        for (int i = points.size() - 1; i >= 0; --i) {
            while (lower_hull.size() >= 2 && ccw(lower_hull[lower_hull.size() - 2], lower_hull[lower_hull.size() - 1], points[i]) <= 0) {
                lower_hull.pop_back();
            }
            lower_hull.push_back(points[i]);
        }

        convex_hull = upper_hull;
        convex_hull.insert(convex_hull.end(), lower_hull.begin() + 1, lower_hull.end() - 1);
        return convex_hull;
    }

private:

    /**
     * @brief CCW - a -> b -> c is counter clockwise if ccw(a, b, c) > 0
     * 
     * @param a 
     * @param b 
     * @param c 
     * 
     * @return long long
     */
    long long ccw(pair<long long, long long> a, pair<long long, long long> b, pair<long long, long long> c) {
        return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
    }

    vector<pair<long long, long long>> points;
};