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

debug_cout dbgcout(false);

bool check_prefix(string s, string t) {
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] != t[i]) {
            return false;
        }
    }
    return true;
}

bool check_suffix(string s, string t) {
    for (int i = 0; i < s.size(); ++i) {
        if (s[s.size() - 1 - i] != t[t.size() - 1 - i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    string s, t;
    cin >> s >> t;

    bool is_prefix = check_prefix(s, t);
    bool is_suffix = check_suffix(s, t);

    if (is_prefix) {
        if (is_suffix) {
            cout << 0 << endl;
        } else {
            cout << 1 << endl;
        }
    } else {
        if (is_suffix) {
            cout << 2 << endl;
        } else {
            cout << 3 << endl;
        }
    }
    
    return 0;
}