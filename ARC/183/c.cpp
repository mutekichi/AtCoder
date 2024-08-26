#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

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

debug_cout dbgcout(false);

template<typename T>
void print_vector(const vector<T>& v, bool debug) {
    for (const auto& elem : v) {
        if (debug) {
            dbgcout << elem << " ";
        } else {
            cout << elem << " ";
        }
    }
    if (debug) {
        dbgcout << endl;
    } else {
        cout << endl;
    }
}

const long long MOD = 998244353;

// a^-1 mod m
long long inv_mod(long long a, long long m) {
    long long b = m, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= m;
    if (u < 0) u += m;
    return u;
}

int main() {
    long long n, m;
    cin >> n >> m;

    vector<pair<long long, long long>> lr(n, {LLONG_MAX, LLONG_MIN});

    for (long long i = 0; i < m; ++i) {
        long long l, r, x;
        cin >> l >> r >> x;
        l--; r--; x--;
        lr[x].first = min(lr[x].first, l);
        lr[x].second = max(lr[x].second, r);
    }

    long long ans = 0;
    vector<long long> factorial_table(n + 1);
    factorial_table[0] = 1;
    for (long long i = 1; i <= n; ++i) {
        factorial_table[i] = (factorial_table[i - 1] * i) % MOD;
    }

    vector<vector<long long>> combination_table(n + 1, vector<long long>(n + 1, 0));
    for (long long i = 0; i <= n; ++i) {
        combination_table[i][0] = 1;
        combination_table[i][i] = 1;
    }
    for (long long i = 1; i <= n; ++i) {
        for (long long j = 1; j < i; ++j) {
            combination_table[i][j] = (combination_table[i - 1][j - 1] + combination_table[i - 1][j]) % MOD;
        }
    }

    vector<long long> inv_mod_table(n + 1);
    for (long long i = 1; i <= n; ++i) {
        inv_mod_table[i] = inv_mod(i, MOD);
    }

    for (long long i = 0; i < n; ++i) {
        dbgcout << ans << endl;
        long long l = lr[i].first;
        long long r = lr[i].second;
        if (l == LLONG_MAX) continue;

        long long range = r - l + 1;
        long long tmp = (factorial_table[n - range] * combination_table[n][range]) % MOD;
        ans = (ans + tmp * factorial_table[range - 1]) % MOD;

        for (long long j = 0; j < i - 1; ++j) {
            long long l2 = lr[j].first;
            long long r2 = lr[j].second;
            if (l2 == LLONG_MAX) continue;
            long long range_2 = r2 - l2 + 1;

            // 包含
            if (l2 <= l && r <= r2) {
                continue;
            } 
            // 背反
            else if (r < l2 || r2 < l) {
                long long tmp = (factorial_table[n] * inv_mod_table[range] % MOD) * inv_mod_table[range_2] % MOD;
                ans = (ans + MOD - tmp) % MOD;
            }
            else {
                if (j > r) {
                    if (i < l2) {
                        long long all_range = r2 - l + 1;
                        long long tmp = factorial_table[n] * inv_mod(combination_table[all_range][2], MOD) % MOD;
                        ans = (ans + MOD - tmp) % MOD;
                    } else {
                        long long min_range = r2 - r + 1;
                        long long tmp = factorial_table[n] * inv_mod(min_range * (min_range - 1ll), MOD) % MOD;
                        ans = (ans + MOD - tmp) % MOD;
                    }
                } else {
                    if (i < l2) {
                        long long min_range = l2 - l + 1;
                        long long tmp = factorial_table[n] * inv_mod(min_range * (min_range - 1ll), MOD) % MOD;
                        ans = (ans + MOD - tmp) % MOD;
                    } else {
                        continue;
                    }
                }
            }
        }
    }
    
    cout << (factorial_table[n] + MOD - ans) % MOD << endl;

    return 0;
}