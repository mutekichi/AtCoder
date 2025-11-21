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
    string s;
    cin >> s;

    int l = s.size();

    vector<pair<int, char>> run_lengths;
    for (int i = 0; i < l; ++i) {
        int j = i;
        while (j < l && s[j] == s[i]) {
            ++j;
        }
        run_lengths.push_back(make_pair(j - i, s[i]));
        i = j - 1;
    }

    int ans = 0;

    for (int i = 1; i < run_lengths.size(); ++i) {
        if (run_lengths[i].second == '/'
            && run_lengths[i - 1].second == '1'
            && run_lengths[i + 1].second == '2') {
                ans = max(ans, min(run_lengths[i - 1].first, run_lengths[i + 1].first));
            }
    }

    cout << ans * 2 + 1 << endl;

    return 0;
}
