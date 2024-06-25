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

long long MOD = 1000000007;

int main() {

    long long n, l;
    cin >> n >> l;

    vector<long long> dp(n + 1, 0);

    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
        dp[i] += dp[i - 1];
        if (i >= l) {
            dp[i] += dp[i - l];
        }
        dp[i] %= MOD;
    }

    cout << dp[n] << endl;
    
    return 0;
}