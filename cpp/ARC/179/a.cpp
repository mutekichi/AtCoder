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

void print_vector(vector<long long> v) {
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i < v.size() - 1) cout << " ";
    }
    cout << endl;
}

int main() {

    int n;
    long long k;
    cin >> n >> k;

    vector<long long> a(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    long long sum_negative = 0;
    long long sum_positive = 0;

    long long sum = 0;

    if (k <= 0) {
        for (int i = 0; i < n; ++i) {
            if (a[i] < 0) {
                sum_negative += a[i];
            } else {
                sum_positive += a[i];
            }
        }
        if (sum_negative + sum_positive < k) cout << "No" << endl;
        else {
            cout << "Yes" << endl;
            sort(a.begin(), a.end(), greater<long long>());
            print_vector(a);
        }
    } else {
        cout << "Yes" << endl;
        sort(a.begin(), a.end());
        print_vector(a);
    }

    return 0;
}