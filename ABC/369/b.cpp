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
    vector<int> L, R;
    for (int i = 0; i < n; ++i) {
        int a;
        char c;
        cin >> a >> c;
        if (c == 'L') {
            L.push_back(a);
        } else {
            R.push_back(a);
        }
    }

    int ans_l = INT_MAX;
    if (L.size() == 0) {
        ans_l = 0;
    }
    else {
        for (int i = 1; i <= 100; ++i) {
            int value = 0;
            int current_pos = L[0];
            for (int j = 0; j < L.size(); ++j) {
                value += abs(L[j] - current_pos);
                current_pos = L[j];
            }
            ans_l = min(ans_l, value);
        }
    }

    int ans_r = INT_MAX;
    if (R.size() == 0) {
        ans_r = 0;
    }
    else {
        for (int i = 1; i <= 100; ++i) {
            int value = 0;
            int current_pos = R[0];
            for (int j = 0; j < R.size(); ++j) {
                value += abs(R[j] - current_pos);
                current_pos = R[j];
            }
            ans_r = min(ans_r, value);
        }
    }

    cout << ans_l + ans_r << endl;

    return 0;
}
