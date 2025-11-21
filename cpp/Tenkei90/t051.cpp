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

void exhaustive_combination(int n, int r, int bitstring = 0, int depth = 0) {
    if (depth == r) {
        for (int i = 0; i < n; ++i) {
            if (bitstring & (1 << i)) {
                // write the code here
                // example:
                // cout << i << " ";
            }
        }
        return;
    }

    for (int i = 0; i < n; ++i) {
        if (bitstring & (1 << i)) {
            continue;
        }
        exhaustive_combination(n, r, bitstring | (1 << i), depth + 1);
    }
}

int main() {

    int n, k;
    cin >> n >> k;

    long long p;
    cin >> p;

    int group1num = n / 2;
    int group2num = n - group1num;

    vector<vector<long long>> group_2(group2num + 1);

    vector<long long> prices(n);
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }
    sort(prices.begin(), prices.end());

    for (int i = 0; i < (1<<group2num); ++i) {
        long long sum = 0;
        for (int j = 0; j < group2num; ++j) {
            if (i & (1 << j)) {
                sum += prices[j + group1num];
            }
        }
        group_2[__builtin_popcount(i)].push_back(sum);
    }

    for (int i = 0; i < group2num + 1; ++i) {
        sort(group_2[i].begin(), group_2[i].end());
    }

    long long ans = 0;

    for (int i = 0; i < (1<<group1num); ++i) {
        long long sum = 0;
        for (int j = 0; j < group1num; ++j) {
            if (i & (1 << j)) {
                sum += prices[j];
            }
        }
        int rest = k - __builtin_popcount(i);

        if (rest < 0 || rest > group2num) {
            continue;
        }

        int itr = upper_bound(group_2[rest].begin(), group_2[rest].end(), p - sum) - group_2[rest].begin();

        ans += (long long)itr;
    }

    cout << ans << endl;

    return 0;
}