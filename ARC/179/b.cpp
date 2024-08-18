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

long long MOD_99 = 998244353;

long long clear_bit(long long bitstring, long long position) {
    long long mask = ~(1<<position);
    return bitstring & mask;
}

long long set_bit(long long bitstring, long long position) {
    long long mask = 1<<position;
    return bitstring | mask;
}

int main() {

    long long m, n;
    cin >> m >> n;

    vector<vector<long long>> recover(m);

    for (long long i = 0; i < m; ++i) {
        long long tmp;
        cin >> tmp;
        tmp--;
        recover[tmp].push_back(i);
    }

    long long max_states = 1 << m;
    vector<vector<long long>> dp(n + 1, vector<long long>(max_states, 0ll));

    for (long long state = 0ll; state < max_states; ++state) {
        if (state == max_states - 1) {
            dp[0][state] = 1ll;
        } else {
            dp[0][state] = 0ll;
        }
    }

    // for (long long i = 1; i <= n; ++i) {
    //     for (long long state = 0; state < max_states; ++state) {
    //         for (long long j = 0; j < m; ++j) { 
    //             if (state & (1 << j)) continue;
    //             else {
    //                 bool ok = true;
    //                 for (auto x : recover[j]) {
    //                     if (state & (1 << x) == 0) {
    //                         ok = false;
    //                         break;
    //                     }
    //                 }
    //                 if (ok) {
    //                     dbgcout << "i: " << i << " state: " << state << " j: " << j << endl;
    //                     long long base_state = state | (1 << j);
    //                     for (long long k = 0; k < (1<<recover[j].size()); ++k) {
    //                         long long new_state = base_state;
    //                         for (long long l = 0; l < recover[j].size(); ++l) {
    //                             if (k & (1 << l)) {
    //                                 new_state |= (1 << recover[j][l]);
    //                             }
    //                         }
    //                         dp[i][state] += dp[i - 1][new_state];
    //                         dp[i][state] %= MOD;
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    for (long long i = 0; i < n; ++i) {
        for (long long state = 0ll; state < max_states; ++state) {
            for (long long j = 0; j < m; ++j) {
                if (state & (1 << j)) {
                    long long next_state = state;
                    next_state = clear_bit(next_state, j);
                    for (long long &pos_to_be_recovered : recover[j]) {
                        next_state = set_bit(next_state, pos_to_be_recovered);
                    }
                    dp[i + 1][next_state] += dp[i][state];
                    dp[i + 1][next_state] %= MOD_99;
                }
            }
        }
    }

    long long sum = 0ll;
    for (long long state = 0ll; state < max_states; ++state) {
        sum += dp[n][state];
        sum %= MOD_99;
    }

    cout << sum << endl;

    return 0;
}