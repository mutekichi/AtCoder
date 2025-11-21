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

    int n, s;
    cin >> n >> s;
    
    vector<vector<bool>> dp(n + 1, vector<bool>(s + 1, false));

    dp[0][0] = true;

    vector<vector<int>> a(n, vector<int>(2, 0));

    for (int i = 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= s; ++j) {
            if (dp[i][j]) {
                for (int k = 0; k <= 1; ++k) {
                    if (j + a[i][k] <= s) {
                        dp[i + 1][j + a[i][k]] = true;
                    }
                }
            }   
        }
    }

    string ans = "";

    if (!dp[n][s]) {
        ans = "Impossible";
    } else {
        int sum = s;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j <= 1; ++j) {
                if (sum - a[i][j] >= 0 && dp[i][sum - a[i][j]]) {
                    ans += (char)('A' + j);
                    sum -= a[i][j];
                    break;
                }
            }
        }
        reverse(ans.begin(), ans.end());
    }

    cout << ans << endl;

    return 0;
}