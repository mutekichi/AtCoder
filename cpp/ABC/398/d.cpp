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

long long encode(long long r, long long c) {
    return r * 100000000ll + c;
}


int main() {

    int n;
    long long r, c;
    cin >> n >> r >> c;

    string s;
    cin >> s;

    vector<pair<long long, long long>> v(n + 1);
    v[n] = make_pair(r, c);

    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == 'N') {
            v[i] = make_pair(v[i + 1].first + 1, v[i + 1].second);
        }
        else if (s[i] == 'S') {
            v[i] = make_pair(v[i + 1].first - 1, v[i + 1].second);
        }
        else if (s[i] == 'E') {
            v[i] = make_pair(v[i + 1].first, v[i + 1].second - 1);
        }
        else if (s[i] == 'W') {
            v[i] = make_pair(v[i + 1].first, v[i + 1].second + 1);
        }
    }

    set<long long> visited;
    for (int i = 0; i < n; ++i) {
        long long 
    }

    return 0;
}
