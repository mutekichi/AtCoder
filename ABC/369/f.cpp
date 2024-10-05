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


template <typename T>
void longest_increasing_subsequence(
    vector<T> &sequence,
    vector<T> &lis,
    int &lis_length
) {
    int n = sequence.size();
    vector<int> dp(n, INT_MAX);
    vector<int> index(n);
    lis_length = 0;

    for (int i = 0; i < n; ++i) {
        index[i] = lower_bound(dp.begin(), dp.end(), sequence[i]) - dp.begin();
        dp[index[i]] = sequence[i];
        lis_length = max(lis_length, index[i] + 1);
    }

    lis.resize(lis_length);
    for (int i = n - 1; i >= 0; --i) {
        if (index[i] == lis_length - 1) {
            lis[--lis_length] = sequence[i];
        }
    }
}

int main() {

    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int lis_length;
    vector<long long> lis;

    longest_increasing_subsequence(a, lis, lis_length);

    cout << lis_length << endl;

    for (int i = 0; i < lis_length; ++i) {
        cout << lis[i] << " ";
    }
    cout << endl;

    return 0;
}
