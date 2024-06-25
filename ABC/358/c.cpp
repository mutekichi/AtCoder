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

int string_to_int(string s, int m) {
    int result = 0;
    for (int i = 0; i < m; ++i) {
        if (s[i] == 'o') {
            result += (1 << i);
        }
    }
    return result;
}

int main() {

    int n, m;
    cin >> n >> m;

    vector<int> a(n);

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        
        a[i] = string_to_int(s, m);
    }

    int min_mise = 100;

    for (int i = 0; i < (1<<n); ++i) {
        int result = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1<<j)) {
                result |= a[j];
            }
        }
        if (result == (1<<m) - 1) {
            min_mise = min(min_mise, __builtin_popcount(i));
        }
    }

    cout << min_mise << endl;
    
    return 0;
}