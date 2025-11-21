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
    for (long long i = 0; i < v.size(); i++) {
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

    string s;
    cin >> s;

    vector<vector<long long>> v(26, vector<long long>());
    vector<long long> counts(26, 0);
    vector<long long> to_add(26, 0);

    for (long long i = 0; i < s.size(); i++) {
        v[s[i] - 'A'].push_back(i);
    }

    long long ans = 0;

    for (long long i = 0; i < s.size(); ++i) {
        long long c = s[i] - 'A';
        for (long long j = 0; j < 26; ++j) {
            if (j == c) {
                counts[j]++;
                ans += to_add[j];
                to_add[j] += counts[j] - 1;
            } else {
                to_add[j] += counts[j];
            }
        }
        // cout << ans << endl;
    }

    cout << ans << endl;

    return 0;
}
