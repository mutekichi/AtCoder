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

int MOD = 1000000007;

int add_mod(int a, int b) {
    return (a + b) % MOD;
}

int main() {

    int n;
    cin >> n;

    string s;
    cin >> s;

    string atcoder = "atcoder";

    vector<vector<int>> dp(n + 1, vector<int>(atcoder.size() + 1, 0));

    dp[0][0] = 1;

    for (int i = 1; i < n + 1; ++i) {
        for (int j = 0; j < atcoder.size() + 1; ++j) {
            if (j == 0) {
                dp[i][j] = dp[i - 1][j];
            } else {
                if (s[i - 1] != atcoder[j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = add_mod(dp[i - 1][j], dp[i - 1][j - 1]);
                }
            }
        }
    }

    // for (int i = 0; i < n + 1; ++i) {
    //     for (int j = 0; j < 8; ++j) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << dp[n][7] << endl;
    
    return 0;
}