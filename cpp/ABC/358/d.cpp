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

int main() {

    unsigned long long n, m;
    cin >> n >> m;

    multiset<unsigned long long> a;
    vector<unsigned long long> b(m);

    for (unsigned long long i = 0; i < n; ++i) {
        unsigned long long ai;
        cin >> ai;
        a.insert(ai);
    }
    for (unsigned long long i = 0; i < m; ++i) {
        unsigned long long bi;
        cin >> bi;
        b[i] = bi;
    }

    unsigned long long ans = 0;

    sort(b.begin(), b.end());

    for (unsigned long long i = 0; i < m; ++i) {
        auto itr = a.lower_bound(b[i]);

        if (itr == a.end()) {
            cout << -1 << endl;
            return 0;
        } else {
            ans += *itr;
            a.erase(itr);
        }
    }

    cout << ans << endl;

    return 0;
}