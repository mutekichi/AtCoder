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

map<long long, long double> memo;

long double expected_value(long long n, int a, long long x, long long y) {
    if (n == 0) return 0.0;

    if (memo.find(n) != memo.end()) return memo[n];

    long double other = 0.0;

    for (int i = 2; i < 7; ++i) {
        other += expected_value(n / i, a, x, y);
    }

    long double ans = min(x + expected_value(n/a, a, x, y), y * 1.2 + other * 1.0 / 5.0);

    memo[n] = ans;

    return ans;
}

int main() {

    long long n;
    int a;
    long long x, y;

    cin >> n >> a >> x >> y;

    cout << fixed << setprecision(20) << expected_value(n, a, x, y) << endl;
    
    return 0;
}