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

unsigned long long mod = 998244353;

// if x is 9, return 4
unsigned long long msb(unsigned long long x) {
    unsigned long long res = 0ll;
    while (x > 0) {
        x >>= 1;
        res++;
    }
    return res - 1ll;
}

unsigned long long add_mod(unsigned long long a, unsigned long long b) {
    return (a + b) % mod;
}

unsigned long long times_mod(unsigned long long a, unsigned long long b) {
    return (a * b) % mod;
}

unsigned long long pow_mod(unsigned long long a, unsigned long long b) {
    unsigned long long res = 1ll;
    for (unsigned long long i = 0; i < b; ++i) {
        res = times_mod(res, a);
    }
    return res;
}

// unsigned long long calc_popcount_sum_for_effective_M(unsigned long long M, long long repeats) {
//     if (M == 0ll) return 0ll;
//     unsigned long long m_msb = msb(M);
//     unsigned long long m_popcount = __builtin_popcountll(M);
//     unsigned long long per1 = m_popcount * pow_mod(2ll, m_msb);
//     return times_mod(per1, repeats);
// }

void print_binary(unsigned long long x) {
    for (int i = 63; i >= 0; --i) {
        cout << ((x >> i) & 1ll);
    }
    cout << endl;
}


unsigned long long calc_popcount_sum(unsigned long long N, unsigned long long M) {
    if (N == 0) return 0ll;
    unsigned long long n_msb = msb(N);
    // print_binary(N);
    // cout << "n_msb: " << n_msb << endl;
    unsigned long long N_upper = 1ll << n_msb;
    unsigned long long N_lower = N ^ N_upper;

    unsigned long long mask = (1ll << n_msb) - 1ll;
    // cout << M << " & " << mask << " = " << (M & mask) << endl;
    unsigned long long effective_M = M & mask;

    unsigned long long res = 0ll;

    if (N_upper & M) {
        res = add_mod(res, N_lower + 1ll);
    }

    unsigned long long m_msb = msb(M);

    unsigned long long repeats = n_msb <= m_msb ? 1 : 1ll << (n_msb - m_msb - 1);
    res = add_mod(res, times_mod(N_upper/2ll, __builtin_popcountll(effective_M)));
    res = add_mod(res, calc_popcount_sum(N_lower, M));

    // cout << "N: " << N << ", M: " << M << ", res: " << res << endl;

    return res;

}

unsigned long long naive(unsigned long long n, unsigned long long m) {
    unsigned long long res = 0ll;
    for (unsigned long long i = 0ll; i <= n; ++i) {
        res += __builtin_popcountll(i & m);
    }
    return res;
}

int main() {

    unsigned long long N, M;
    cin >> N >> M;

    // print_binary(N);
    // print_binary(M);

    cout << calc_popcount_sum(N, M) << endl;
    // cout << naive(N, M) << endl;
    
    return 0;
}