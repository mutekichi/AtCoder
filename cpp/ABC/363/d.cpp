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

long long count_n_keta_kaibun(long long n) {
    if (n == 1ll) {
        return 9ll;
    }
    else if (n == 2) {
        return 9ll;
    }
    else {
        return 10ll * count_n_keta_kaibun(n - 2ll);
    }
}

long long pow(long long x, long long n) {
    long long res = 1ll;
    for (int i = 0ll; i < n; i++) {
        res *= x;
    }
    return res;
}

long long getHighestDigit(long long number) {
    if (number == 0ll) return 0ll;
    
    while (number >= 10ll) {
        number /= 10ll;
    }
    
    return number;
}


long long kthSmallestNumber(long long n, long long k) {
    if (n == 1ll) {
        return k;
    }
    else {
        long long highest_digit = getHighestDigit(k);
        long long rest = k - highest_digit * pow(10ll, n - 1ll);
        
        return (highest_digit + 1ll) * pow(10ll, n - 1ll) + rest - 1ll;
    }
}


int main() {

    long long n;
    cin >> n;

    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }

    vector<long long> n_keta_kaibun(50ll);
    vector<long long> accum_n_keta_kaibun(50ll);

    n_keta_kaibun[0] = 1ll;
    accum_n_keta_kaibun[0] = 1ll;

    for (int i = 1; i < 50ll; ++i) {
        n_keta_kaibun[i] = count_n_keta_kaibun(i);
        accum_n_keta_kaibun[i] = accum_n_keta_kaibun[i - 1] + n_keta_kaibun[i];
    }

    // print_vector(n_keta_kaibun);
    // print_vector(accum_n_keta_kaibun);
    
    long long accum_kaibun_count = 0ll;
    long long n_keta = 0ll;

    while(accum_kaibun_count < n) {
        accum_kaibun_count += n_keta_kaibun[n_keta];
        n_keta++;
    }
    n_keta--;

    long long amari = n - accum_n_keta_kaibun[n_keta - 1ll];

    // cout << "n_keta " << n_keta << endl;
    // cout << amari << endl;

    long long ans__ = kthSmallestNumber((n_keta + 1ll) / 2ll, amari);

    string s_n = to_string(ans__);

    string inverse_s_n = s_n;
    for (int i = 0ll; i < s_n.size(); i++) {
        inverse_s_n[s_n.size() - i - 1ll] = s_n[i];
    }

    if (n_keta % 2ll == 0) {
        cout << s_n << inverse_s_n << endl;
    } else {
        cout << s_n << inverse_s_n.substr(1ll, inverse_s_n.size() - 1ll) << endl;
    }

    return 0;
}
