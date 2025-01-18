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

    vector<int> a(n);
    vector<int> b(n - 1);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < n - 1; ++i) {
        cin >> b[i];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int ai = n - 1;
    int bi = n - 2;

    int ans = -1;

    for (int i = 0; i < n; ++i) {
        if (ai < 0 || bi < 0) {
            cout << a[0] << endl;
            return 0;
        }

        // cout << "compare a[" << ai << "] = " << a[ai] << " and b[" << bi << "] = " << b[bi] << endl;

        if (a[ai] <= b[bi]) {
            ai--;
            bi--;
        }
        else {
            if (ans == -1) {
                ans = a[ai];
                ai--;
            } else {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
