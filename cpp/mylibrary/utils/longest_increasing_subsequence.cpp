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

template <typename T>
void longest_increasing_subsequence(
    vector<T> &sequence,
    vector<T> &lis,
    int &lis_length
) {
    int n = sequence.size();
    vector<int> dp(n, INT_MAX);
    vector<int> index(n);
    lis_length = 0;

    for (int i = 0; i < n; ++i) {
        index[i] = lower_bound(dp.begin(), dp.end(), sequence[i]) - dp.begin();
        dp[index[i]] = sequence[i];
        lis_length = max(lis_length, index[i] + 1);
    }

    lis.resize(lis_length);
    for (int i = n - 1; i >= 0; --i) {
        if (index[i] == lis_length - 1) {
            lis[--lis_length] = sequence[i];
        }
    }
}