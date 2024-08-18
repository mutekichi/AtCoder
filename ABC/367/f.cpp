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

template<typename T>
void print_vector(vector<T> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

debug_cout dbgcout(true);

long long MOD_99 = 998244353ll;
long long MOD_10 = 1000000007ll;

// a^{-1} mod m
long long mod_inv(long long a, long long m) {
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

    int n, q;
    cin >> n >> q;

    vector<long long> a(n), b(n);

    vector<long long> ia99(n), ib99(n); // inv_a, inv_b
    vector<long long> aia99(n + 1, 0), aib99(n + 1, 0); // accum_inv_a, accum_inv_b

    vector<long long> ia10(n), ib10(n); // inv_a, inv_b
    vector<long long> aia10(n + 1, 0), aib10(n + 1, 0); // accum_inv_a, accum_inv_b

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]++;
        ia99[i] = mod_inv(a[i], MOD_99);
        aia99[i + 1] = (aia99[i] + ia99[i]) % MOD_99;
        a[i]++;
        ia10[i] = mod_inv(a[i], MOD_10);
        aia10[i + 1] = (aia10[i] + ia10[i]) % MOD_10;
    }

    for (int i = 0; i < n; i++) {
        cin >> b[i];
        b[i]++;
        ib99[i] = mod_inv(b[i], MOD_99);
        aib99[i + 1] = (aib99[i] + ib99[i]) % MOD_99;
        b[i]++;
        ib10[i] = mod_inv(b[i], MOD_10);
        aib10[i + 1] = (aib10[i] + ib10[i]) % MOD_10;
    }
    
    for (int i = 0; i < q; i++) {
        int al, ar, bl, br;
        cin >> al >> ar >> bl >> br;
        al--; ar--; bl--; br--;

        if (ar - al != br - bl) {
            cout << "No" << endl;
            continue;
        } else {
            long long suma99 = (aia99[ar + 1] - aia99[al] + MOD_99) % MOD_99;
            long long sumb99 = (aib99[br + 1] - aib99[bl] + MOD_99) % MOD_99;

            long long suma10 = (aia10[ar + 1] - aia10[al] + MOD_10) % MOD_10;
            long long sumb10 = (aib10[br + 1] - aib10[bl] + MOD_10) % MOD_10;

            if (suma99 == sumb99 && suma10 == sumb10) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }

    return 0;
}
