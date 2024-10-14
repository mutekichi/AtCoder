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

int main() {

    long long n, m, k;
    cin >> n >> m >> k;

    vector<long long> a(n);
    vector<pair<long long, int>> ans(n);

    for (long long i = 0; i < n; i++) {
        cin >> a[i];
        ans[i].first = a[i];
        ans[i].second = i;
        k -= a[i];
    }

    dbgcout << "k: " << k << endl;

    sort(a.begin(), a.end());
    sort(ans.begin(), ans.end());

    long long top_sum_m1 = 0;

    for (int i = 0; i < m - 1; ++i) {
        top_sum_m1 += a[n - 1 - i];
    }

    long long top_sum_m = top_sum_m1 + a[n - m];

    // vector<long long> ans(n);

    for (int i = 0; i < n - m + 1; ++i) {
        long long sum = top_sum_m1 + a[n - m - i] + k;
        long long needed = sum / m;
        if (sum % m != 0) {
            needed++;
        }
        if (needed >= a[n - 1]) {
            ans[i].first = needed - a[n - m - i];
        } else {
            ans[i].first = -1;
        }
    }
    long long needed = (top_sum_m + k) / m;
    if ((top_sum_m + k) % m != 0) {
        needed++;
    }

    for (int i = n - m + 1; i < n; ++i) {
        if (needed >= a[n - 1]) {
            ans[i].first = needed - a[n - m - i];
        } else {
            ans[i].first = -1;
        }
    }

    sort(ans.begin(), ans.end(), [](pair<long long, int> a, pair<long long, int> b) {
        return a.second < b.second;
    });

    for (int i = 0; i < n; ++i) {
        cout << ans[i].first << " ";
    }
    cout << endl;

    return 0;
}
