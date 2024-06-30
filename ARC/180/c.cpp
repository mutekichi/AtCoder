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
#include <assert.h>
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

long long mod = 1000000007ll;

int main() {

    long long n;
    cin >> n;
    vector<long long> a(n);
    for (long long i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long min_value = -10ll * n;
    long long max_value = 10ll * n;

    // vector<vector<pair<long long, bool>>> dp(n+1ll, vector<pair<long long, bool>>(max_value - min_value + 1ll, make_pair(0ll, false)));

    // dp[0][0 - min_value] = make_pair(1ll, false);

    // for (long long i = 1; i <= n; i++) {
    //     for (long long j = 0; j <= max_value - min_value; j++) {
    //         dp[i][j] = dp[i - 1][j];
    //         if (j - a[i - 1] >= 0 && j - a[i - 1] <= max_value - min_value) {
    //             dp[i][j] += dp[i - 1][j - a[i - 1]];
    //         }
    //         dp[i][j] %= mod;
    //     }
    // }

    vector<vector<vector<long long>>> dp(
        n + 1ll,
        vector<vector<long long>>(
            max_value - min_value + 1ll,
            vector<long long>(2, 0ll)
        )
    );

    dp[0][0 - min_value][0] = 1ll;

    for (int i = 1; i <= n; ++i) {
        for (long long j = 0ll; j <= max_value - min_value; ++j) {
            dp[i][j][0] = dp[i - 1][j][0] + dp[i - 1][j][1];
            dp[i][j][0] %= mod;
            if (j - a[i - 1] >= 0 && j - a[i - 1] <= max_value - min_value) {
                dp[i][j][1] = dp[i - 1][j - a[i - 1]][0] + dp[i - 1][j - a[i - 1]][1];
                dp[i][j][1] %= mod;
            }
        }
    }

    long long ans = 0ll;

    for (long long j = 0; j <= max_value - min_value; ++j) {
        ans += dp[n][j][1];
        ans %= mod;
    } cout << ans << endl;

    return 0;
}
