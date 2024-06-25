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

class debug_cout {
public:
    debug_cout(bool debug) : debug(debug) {}

    template<typename T>
    debug_cout& operator<<(const T& value) {
        if (debug) {
            cout << value;
        }
        return *this;
    }

    debug_cout& operator<<(std::ostream& (*manip)(std::ostream&)) {
        if (debug) {
            manip(std::cout);
        }
        return *this;
    }

private:
    bool debug;
};

debug_cout dbgcout(true);

long long mod = 998244353;

long long modpow(long long a, long long n) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int main() {

    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    long long hatena = 0ll;
    for (int i = 0; i < k; ++i) {
        if (s[i] == '?') ++hatena;
    }

    vector<bool> is_kaibun((1<<k), false);
    for (int i = 0; i < (1<<k); ++i) {
        bool is_kaibun_flag = true;
        for (int j = 0; j < k; ++j) {
            if (i & (1<<j)) {
                if (s[j] != s[k+j]) {
                    is_kaibun_flag = false;
                    break;
                }
            }
        }
        is_kaibun[i] = is_kaibun_flag;
    }

    vector<vector<long long>> dp(n - k, vector<long long>((1<<(k - 1)), 0ll));

    for (int j = 0; j < (1<<(k - 1)); ++j) {
        if (is_kaibun[j]) {
            for (int bit_i = 0; bit_i < k; ++bit_i) {
                if (j & (1<<bit_i)) {
                    if (s[bit_i] == 'A' || s[bit_i] == '?') {
                        dp[0][j] = (dp[0][j] + 1) % mod;
                    }
                } else {
                    if (s[bit_i] == 'B' || s[bit_i] == '?') {
                        dp[0][j] = (dp[0][j] + 1) % mod;
                    }
                }
            }
        }
    }

    for (int i = 1; i < n - k; ++i) {
        for (int j = 0; j < (1<<(k - 1)); ++j) {
            if (is_kaibun[j]) {
                if (s[i + k - 1] == 'A') {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j >> 1]) % mod;
                } else if (s[i + k - 1] == 'B') {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j >> 1 | (1<<(k - 2))]) % mod;
                } else {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j >> 1]) % mod;
                    dp[i][j] = (dp[i][j] + dp[i - 1][j >> 1 | (1<<(k - 2))]) % mod;
                }
            }
        }
    }

    long long ans = 0ll;
    for (int j = 0; j < (1<<(k - 1)); ++j) {
        ans = (ans + dp[n - k - 1][j]) % mod;
    }

    cout << (modpow(2, n) + mod - ans) % mod << endl;

    return 0;
}