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

int main() {

    int n;
    cin >> n;

    vector<pair<long long, long long>> LR(n);

    for (int i = 0; i < n; ++i) {
        long long l, r;
        cin >> l >> r;
        if (l > r) swap(l, r);
        LR[i] = make_pair(l, r);
    }

    long long sum_min = 0ll;
    long long sum_max = 0ll;

    for (int i = 0; i < n; ++i) {
        sum_min += LR[i].first;
        sum_max += LR[i].second;
    }

    vector<long long> ans(n);

    if (sum_min <= 0 && 0 <= sum_max) {
        cout << "Yes" << endl;

        
        long long to_added = -1ll * sum_min;

        for (int i = 0; i < n; ++i) {
            if (to_added > 0ll) {
                if (to_added >= LR[i].second - LR[i].first) {
                    to_added -= LR[i].second - LR[i].first;
                    ans[i] = LR[i].second;
                } else {
                    ans[i] = LR[i].first + to_added;
                    to_added = 0ll;
                }
            } else {
                ans[i] = LR[i].first;
            }
        }

        for (int i = 0; i < n; ++i) {
            cout << ans[i];
            if (i != n - 1) cout << " ";
            else cout << endl;
        }

    } else cout << "No" << endl;

    return 0;
}
