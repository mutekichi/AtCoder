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

    vector<vector<bool>> vec(
        (1<<20), vector<bool>(20 + 1, false)
    );

    vector<set<int>> can_add_a(
        20, set<int>()
    );

    set<int> can_add_any;

    can_add_any.insert(0);

    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        a--;
        
        set<int> can_add_a_copy = can_add_a[a];

        for (auto j : can_add_any) {
            can_add_a[a].insert(j);
            vec[j][a] = true;
        }

        for (auto j : can_add_a_copy) {
            vec[j | (1 << a)][20] = true;
            can_add_any.erase(j);
            can_add_any.insert(j | (1 << a));
        }
    }

    int ans = 0;

    for (int i = 0; i < (1 << 20); ++i) {
        if (vec[i][20]) {
            ans = max(ans, __builtin_popcount(i));
        }
    }

    cout << ans * 2 << endl;

    return 0;
}
