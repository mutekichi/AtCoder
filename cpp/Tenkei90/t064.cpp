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

int main() {
    int n, q;
    cin >> n >> q;

    vector<long long> diffs(n);
    for (int i = 0; i < n; ++i) {
        cin >> diffs[i];
    }
    long long score = 0ll;

    for (int i = n - 1; i > 0; --i) {
        diffs[i] = diffs[i] - diffs[i - 1];
        score += abs(diffs[i]);
    }
    diffs[0] = 0ll;

    int l, r;
    long long v;

    for (int i = 0; i < q; ++i) {
        cin >> l >> r;
        cin >> v;

        l--; r--;
        if (l > 0) {
            long long prev_diff = diffs[l];
            diffs[l] += v;
            score += abs(diffs[l]) - abs(prev_diff);
        }
        if (r < n - 1) {
            long long prev_diff = diffs[r + 1];
            diffs[r + 1] -= v;
            score += abs(diffs[r + 1]) - abs(prev_diff);
        }

        cout << score << endl;
    }
    return 0;
}