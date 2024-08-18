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
    for (long long i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

debug_cout dbgcout(false);

int main() {

    long long n, m;
    cin >> n >> m;

    long long sum = 0;

    vector<long long> a(n);
    for (long long i = 0; i < n; i++) {
        long long b;
        cin >> b;
        a[i] = b % m;
        sum += a[i];
        sum %= m;
    }
    vector<long long> accum_a(n);
    accum_a[0] = 0;

    vector<vector<long long>> mod_map(m);

    for (long long i = 0; i < n - 1; ++i) {
        accum_a[i + 1] = (accum_a[i] + a[i]) % m;
    }

    for (long long i = 0; i < n; ++i) {
        mod_map[accum_a[i]].push_back(i);
    }

    long long ans = 0;

    for (long long i = 0; i < n; ++i) {
        dbgcout << "i: " << i << endl;
        long long mod = accum_a[i];
        long long res1 = mod;
        long long res2 = (mod + m - sum) % m;
        dbgcout << "mod: " << mod << " res1: " << res1 << " res2: " << res2 << endl;
        vector<long long> &v1 = mod_map[res1];
        // i < v1[j] なる j の数
        // v1 is sorted
        
        ans += v1.end() - upper_bound(v1.begin(), v1.end(), i);

        vector<long long> &v2 = mod_map[res2];
        // i > v2[j] なる j の数
        ans += lower_bound(v2.begin(), v2.end(), i) - v2.begin();
    }

    cout << ans << endl;

    return 0;
}