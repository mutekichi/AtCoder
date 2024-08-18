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

int pow(int a, int b) {
    int res = 1;
    for (int i = 0; i < b; i++) {
        res *= a;
    }
    return res;
}

int main() {

    int n, k;
    cin >> n >> k;
    vector<int> r(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    for (int i = 0; i < pow(5, n); ++i) {
        vector<int> current(n);
        for (int j = 0; j < n; ++j) {
            current[n - j - 1] = (i / pow(5, j)) % 5 + 1;
        }
        bool ok = true;
        for (int j = 0; j < n; ++j) {
            if (current[j] > r[j]) {
                ok = false;
                break;
            }
        }
        if (!ok) continue;
        int sum = 0;
        for (int j = 0; j < n; ++j) {
            sum += current[j];
        }
        if (sum % k == 0) {
            print_vector(current);
        }
    }


    return 0;
}
