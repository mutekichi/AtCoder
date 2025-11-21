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

template<typename T>
void print_vector(vector<T> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

debug_cout dbgcout(true);


long long reverse_bit(long long n, long long k) {
    long long result = 0;
    for (long long i = 0; i < k; ++i) {
        if (n & (1 << i)) {
            result += (1 << (k - i - 1));
        }
    }
    return result;
}

int main() {

    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        long long n, k;
        cin >> n >> k;

        vector<long long> ans(n);
        // base = 111...1
        long long base = (1ll << k) - 1ll;

        for (long long j = 0; j < n; ++j) {
            if (j >= (1<<(k - 1))) {
                ans[j] = 1ll;
            } else {
                ans[j] = base ^ reverse_bit(j, k - 1);
            }
        }

        for (long long j = 0; j < n; ++j) {
            if (j > 0) {
                cout << " ";
            }
            cout << ans[j];
        }
        cout << endl;
    }

    return 0;
}
