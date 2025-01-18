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

void f(vector<int> v, int res1, int res2, int val, vector<vector<int>>& ans) {

    // dbgcout << "res1: " << res1 << " res2: " << res2 << " val: " << val << endl;
    if (res2 == 0) {
        ans.push_back(v);
        return;
    }
    for (int i = 0; i <= res1; ++i) {
        vector<int> v2 = v;
        v2.push_back(val + 10 + i);
        f(v2, res1 - i, res2 - 1, val + 10 + i, ans);
    }
}

int main() {

    int n, m;
    cin >> n >> m;

    vector<vector<int>> ans;

    vector<int> empty;

    int res1 = m - (10 * n - 9);
    int res2 = n;
    f(empty, res1, res2, -9, ans);

    cout << ans.size() << endl;

    for (int i = 0; i < ans.size(); ++i) {
        for (int j = 0; j < ans[i].size(); ++j) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
