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

long long MOD = 1000000007ll;

int main() {

    long long k;
    cin >> k;

    if (k % 9 != 0) {
        cout << 0 << endl;
        return 0;
    }

    vector<vector<long long>> dp(k, vector<long long>(9, 0));

    dp[0][0] = 1ll;

    for (long long i = 1; i < k; ++i) {
        for (long long j = 0; j < 9; ++j) {
            if (j == 0) {
                for (long long k = 0; k < 9; ++k) {
                    dp[i][j] += dp[i - 1][k];
                    dp[i][j] %= MOD;
                }
            } else {
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }

    long long ans = 0ll;
    for (long long i = 0; i < 9; ++i) {
        ans += dp[k - 1][i];
        ans %= MOD;
    }
    cout << ans << endl;
    
    return 0;
}