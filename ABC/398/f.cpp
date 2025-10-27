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

template<typename T>
void output_vector(vector<T> v, bool debug) {
    for (int i = 0; i < v.size(); i++) {
        if (debug) {
            dbgcout << v[i] << " ";
        }
        else {
            cout << v[i] << " ";
        }
    }
    if (debug) {
        dbgcout << endl;
    }
    else {
        cout << endl;
    }
}

long long mod_pow(long long x, long long n, long long mod) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) {
            res = res * x % mod;
        }
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

long long to_ll(char c) {
    long long ans = (long long)(c - 'A');
    return ans;
}

int main() {
    string s;
    cin >> s;

    string ans = "";

    if (s.size() % 2 == 1) {
        ans += s[0];
        s = s.substr(1);
    }

    const int len = s.size() / 2;
    
    vector<long long> hashed_prev(2, 0);
    vector<long long> hashed_next(2, 0);
    vector<long long> mods(2);
    long long base = 26;
    vector<vector<long long>> pow_table(2, vector<long long>(len + 1, 1));

    
    mods[0] = 1000000007;
    mods[1] = 1000000009;

    for (int i = 0; i < 2; ++i) {
        for (int j = 1; j <= len; ++j) {
            pow_table[i][j] = pow_table[i][j - 1] * base % mods[i];
        }
    }

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < len; ++j) {
            hashed_prev[i] += to_ll(s[len - j - 1]) * pow_table[i][j] % mods[i];
            hashed_prev[i] %= mods[i];
            hashed_next[i] += to_ll(s[len + j]) * pow_table[i][j] % mods[i];
            hashed_next[i] %= mods[i];
        }
    }

    long long pow_offset = 0;
    long long cur_len = len;
    long long pivot = len;

    while(cur_len > 0) {
        bool is_same = true;
        for (int j = 0; j < 2; ++j) {
            if (hashed_prev[j] * pow_table[j][pow_offset] % mods[j] != hashed_next[j]) {
                is_same = false;
                break;
            }
        }
        if (is_same) {
            for (int i = 0; i < cur_len; ++i) {
                ans = ans + s[pivot - cur_len + i];
            }
        }

        for (int j = 0; j < 2; ++j) {
            hashed_prev[j] += (3ll * mods[j]);
            hashed_prev[j] -= to_ll(s[pivot - cur_len]) * pow_table[j][cur_len - 1] % mods[j];
            hashed_prev[j] -= to_ll(s[pivot - cur_len + 1]) * pow_table[j][cur_len - 2] % mods[j];
            hashed_prev[j] %= mods[j];
            hashed_prev[j] *= base;
            hashed_prev[j] %= mods[j];
            hashed_prev[j] += to_ll(s[pivot]) % mods[j];
            hashed_prev[j] %= mods[j];

            hashed_next[j] += (3ll * mods[j]);
            hashed_next[j] -= to_ll(s[pivot]) * pow_table[j][pow_offset] % mods[j];
            hashed_next[j] %= mods[j];
        }
        
        ans = ans + s[pivot - cur_len];
        ans = ans + s[pivot - cur_len + 1];

        pivot++;
        cur_len--;
        pow_offset++;

    }

    return 0;
}
 