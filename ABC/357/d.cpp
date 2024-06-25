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

debug_cout dbgcout(false);

long long MOD = 998244353ll;

long long ketasuu(long long n) {
    long long ans = 0ll;
    while (n > 0ll) {
        n /= 10ll;
        ++ans;
    }
    return ans;

}


long long pow_mod(long long base, long long exp) {
    long long result = 1ll;

    if (exp == 0) {
        return 1ll;
    } 
    else {
        long long half = pow_mod(base, exp / 2ll);
        half = half * half % MOD;
        if (exp % 2ll == 1ll) {
            return base * half % MOD;
        } else {
            return half;
        }
    }
}

long long modinv(long long a, long long m) {
	long long b = m, u = 1ll, v = 0ll;
	while (b) {
		long long t = a / b;
		a -= t * b; swap(a, b);
		u -= t * v; swap(u, v);
	}
	u %= m;
	if (u < 0) u += m;
	return u;
}

long long div_mod(long long a, long long b) {
    a %= MOD;
    return a * modinv(b, MOD) % MOD;
}

int main() {

    long long n;
    cin >> n;

    // long long a = n * ketasuu(n);
    long long a = n % (MOD - 1ll) * ketasuu(n);

    dbgcout << a << endl;

    long long b = pow_mod(10ll, a);

    dbgcout << b << endl;

    long long c = (b + MOD - 1ll) % MOD;

    dbgcout << c << endl;

    long long d = n % MOD * c;

    dbgcout << d << endl;

    long long e = pow_mod(10ll, ketasuu(n));

    dbgcout << e << endl;

    long long f = (e + MOD - 1ll) % MOD;

    dbgcout << f << endl;

    long long g = div_mod(d, f);

    cout << g << endl;
    
    return 0;
}