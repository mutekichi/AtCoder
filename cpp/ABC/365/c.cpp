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

debug_cout dbgcout(false);

int main() {

    long long n;
    long long max_a;
    cin >> n >> max_a;
    vector<long long> a(n);

    long long a_sum = 0ll;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a_sum += a[i];
    }

    if (a_sum <= max_a)  {
        cout << "infinite" << endl;
        return 0;
    }

    sort(a.begin(), a.end(), greater<long long>());

    for (long long i = 0; i < n - 1; ++i) {

        dbgcout << "a_sum: " << a_sum << endl;
        dbgcout << (a[i] - a[i + 1]) * (i + 1ll) << endl;

        if (a_sum - (a[i] - a[i + 1]) * (i + 1ll) <= max_a) {
            dbgcout << "i: " << i << endl;
            dbgcout << "a[i]: " << a[i] << endl;
            dbgcout << "a[i + 1]: " << a[i + 1] << endl;
            a_sum -= (a[i] - a[i + 1ll]) * (i + 1ll);

            cout << a[i + 1] + (max_a - a_sum) / (i + 1ll) << endl;
            return 0;
        }
        else {
            a_sum -= (a[i] - a[i + 1ll]) * (i + 1ll);
        }
    }

    cout << max_a / n << endl;
    
    return 0;
}
