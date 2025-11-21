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

int longest_increasing_subsequence(vector<long long> &sequence) {
    int n = sequence.size();
    vector<long long> dp(n, LLONG_MAX);

    for (int i = 0; i < n; ++i) {
        *lower_bound(dp.begin(), dp.end(), sequence[i]) = sequence[i];
    }

    return lower_bound(dp.begin(), dp.end(), LLONG_MAX) - dp.begin();
}

debug_cout dbgcout(true);

int main() {

    int n;
    cin >> n;

    vector<long long> a(n, -1);
    vector<long long> b(n - 1, -1);
    vector<long long> c(n - 1, -1);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i != 0) b[i - 1] = a[i];
        if (i != n - 1) c[i] = a[i];
    }

    int la = longest_increasing_subsequence(a);
    int lb = longest_increasing_subsequence(b);
    int lc = longest_increasing_subsequence(c);

    cout << la << " " << lb << " " << lc << endl;

    if (la - 1 == lb && la - 1 == lc && a[n - 1] - a[0] == la -1) cout << la << endl;
    else {
        if (la == n) cout << la << endl;
        else cout << la + 1 << endl;
    }
    return 0;
}
