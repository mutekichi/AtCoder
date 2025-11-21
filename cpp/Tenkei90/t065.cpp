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

long long MOD_99 = 998244353ll;

// calc 1/a mod m
long long inv(long long a, long long mod) {
    long long b = mod, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= mod;
    if (u < 0) u += mod;
    return u;
}

long long nCr(long long n, long long r, vector<long long> &factorials, vector<long long> &inv_factorials) {
    return factorials[n] * inv_factorials[r] % MOD_99 * inv_factorials[n - r] % MOD_99;
}

int main() {
    
    int R, G, B, K;
    cin >> R >> G >> B >> K;
    int X, Y, Z;
    cin >> X >> Y >> Z;

    int r_min = K - Y;
    int g_min = K - Z;


    vector<long long> factorials(max(R, max(G, B)) + 1);
    vector<long long> inv_factorials(max(R, max(G, B)) + 1);

    factorials[0] = 1ll;
    for (int i = 1; i <= max(R, max(G, B)); ++i) {
        factorials[i] = factorials[i - 1] * i % MOD_99;
    }

    inv_factorials[max(R, max(G, B))] = inv(factorials[max(R, max(G, B))], MOD_99);
    for (int i = max(R, max(G, B)) - 1; i >= 0; --i) {
        inv_factorials[i] = inv_factorials[i + 1] * (i + 1) % MOD_99;
    }

    long long ans = 0ll;

    for (int r = r_min; r <= R; ++r) {
        for (int g = g_min; g <= min(G, X - r); ++g) {
            int b = K - r - g;
            if (b >= 0 && b <= B) {
                ans += nCr(R, r, factorials, inv_factorials) * nCr(G, g, factorials, inv_factorials) % MOD_99 * nCr(B, b, factorials, inv_factorials) % MOD_99;
                ans %= MOD_99;
            }
        }
    }

    cout << ans << endl;

    return 0;
}