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

    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    long long ans = 0;
    ans += n;

    vector<long long> diffs(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        diffs[i] = a[i + 1] - a[i];
    }

    // cout arithmetic progression
    int current_diff = diffs[0];
    int current_count = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (diffs[i] == current_diff) {
            current_count++;
        } else {
            ans += current_count * (current_count + 1ll) / 2ll;
            current_diff = diffs[i];
            current_count = 1ll;
        }
    }

    ans += current_count * (current_count + 1ll) / 2ll;
    cout << ans << endl;

    return 0;
}
