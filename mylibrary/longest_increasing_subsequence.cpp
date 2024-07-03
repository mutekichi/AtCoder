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

int longest_increasing_subsequence(vector<long long> &sequence) {
    int n = sequence.size();
    vector<long long> dp(n, LLONG_MAX);

    for (int i = 0; i < n; ++i) {
        *lower_bound(dp.begin(), dp.end(), sequence[i]) = sequence[i];
    }

    return lower_bound(dp.begin(), dp.end(), LLONG_MAX) - dp.begin();
}