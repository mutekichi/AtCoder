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
#include <iomanip>
#include <cstdlib>
#include <iomanip>

using namespace std;

long long MOD_99 = 998244353ll;

int main() {

    long long k;
    cin >> k;

    // combination_table[i][j] = iCj
    vector<vector<long long>> combination_table = vector<vector<long long>>(1000 + 1, vector<long long>(1000+ 1, 0ll));

    for (int i = 0; i <1001; ++i) {
        combination_table[i][0] = 1ll;
        combination_table[i][i] = 1ll;
    }
    for (int i = 1; i < 1001; ++i) {
        for (int j = 1; j < i; ++j) {
            combination_table[i][j] = (combination_table[i - 1][j - 1] + combination_table[i - 1][j]) % MOD_99;
        }
    }

    int alphabets = 26;
    vector<long long> alphabet_count = vector<long long>(alphabets, 0ll);
    for (int i = 0; i < alphabets; ++i) {
        cin >> alphabet_count[i];
    }

    vector<vector<long long>> dp = vector<vector<long long>>(alphabets, vector<long long>(1000 + 1, 0ll));

    for (int alphabet = 0; alphabet < alphabets; ++alphabet) {
        dp[alphabet][0] = 1ll;
    }
    for (int len = 0; len <= (int)alphabet_count[0]; ++len) {
        dp[0][len] = 1ll;
    }

    for (int alphabet = 1; alphabet < alphabets; ++alphabet) {
        for (int len = 1; len <= k; ++len) {
            for (int alphabet_added = 0; alphabet_added <= alphabet_count[alphabet]; ++alphabet_added) {
                if (len - alphabet_added < 0) {
                    break;
                }
                dp[alphabet][len] += (dp[alphabet - 1][len - alphabet_added] * combination_table[len][alphabet_added]) % MOD_99;
                dp[alphabet][len] %= MOD_99;
            }
        }
    }

    // for (int alphabet = 0; alphabet < alphabets; ++alphabet) {
    //     for (int len = 0; len <= k; ++len) {
    //         cout << dp[alphabet][len] << " ";
    //     }
    //     cout << endl;
    // }

    long long ans = 0ll;
    for (int len = 1; len <= k; ++len) {
        ans += dp[alphabets - 1][len];
        ans %= MOD_99;
    }

    cout << ans << endl;

    return 0;
    
}