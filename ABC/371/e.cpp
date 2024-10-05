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
void print_vector(vector<T> v, bool debug) {
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

    vector<long long> x(n);
    vector<long long> p(n);

    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        cin >> p[i];
    }

    vector<pair<long long, int>> sorted_x(n);
    for (int i = 0; i < n; ++i) {
        sorted_x[i] = make_pair(x[i], i);
    }

    sort(sorted_x.begin(), sorted_x.end());

    vector<long long> accum_sum(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        accum_sum[i + 1] = accum_sum[i] + p[i];
    }

    int q;
    cin >> q;

    for (int i = 0; i < n; ++i) {
        long long l, r;
        cin >> l >> r;

        int left = lower_bound(sorted_x.begin(), sorted_x.end(), make_pair(l, -1)) - sorted_x.begin();
        int right = upper_bound(sorted_x.begin(), sorted_x.end(), make_pair(r, LLONG_MAX)) - sorted_x.begin();

        int left_index = sorted_x[left].second;
        int right_index = sorted_x[right].second;

        cout << accum_sum[right] - accum_sum[left] << endl;
    }

    return 0;
}
