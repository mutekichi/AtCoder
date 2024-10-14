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

debug_cout dbgcout(false);

template<typename T>
void output_vector(vector<T> v, bool debug = false) {
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
    long long k;
    cin >> n >> k;

    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        x[i]--;
    }

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> doubling_table(60, vector<int>(n, -1));

    for (int i = 0; i < n; ++i) doubling_table[0][i] = x[i];

    for (int i = 1; i < 60; ++i) {
        for (int j = 0; j < n; ++j) {
            doubling_table[i][j] = doubling_table[i - 1][doubling_table[i - 1][j]];
        }
    }

    vector<int> current(n);
    for (int i = 0; i < n; ++i) {
        current[i] = i;
    }

    for (int i = 0; i < 60; ++i) {
        if ((k >> i) & 1ll) {
            vector<int> next(n);
            for (int j = 0; j < n; ++j) {
                next[j] = doubling_table[i][current[j]];
            }
            current = next;
        }
    }

    for (int i = 0; i < n; ++i) {
        current[i] = a[current[i]];
    }

    output_vector(current);

    return 0;
}