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
#include <iomanip>

using namespace std;

long double PI = 3.14159265358979323846;

long double kaitenkaku(long double T, long double t) {
    return 2.0 * PI * (long double)t / (long double)T;
}

long double calc_fukaku(long double vx, long double vy, long double vz) {
    return atan2(vz, sqrt(vx * vx + vy * vy));
}

int main() {

    long double T;
    cin >> T;

    long double L, x, y;
    cin >> L >> x >> y;

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        long double t;
        cin >> t;
        long double e8z = (long double)L / 2. * (1 - cos(kaitenkaku(T,t)));
        long double e8y = - (long double)L / 2. * sin(kaitenkaku(T,t));

        // cout << e8y << " " << e8z << endl;

        long double fukaku = calc_fukaku((long double)x, (long double)y - e8y, e8z);

        // cout << fukaku << endl;

        cout << fixed << setprecision(10) << fukaku / PI * 180. << endl;
    }
    
    return 0;
}