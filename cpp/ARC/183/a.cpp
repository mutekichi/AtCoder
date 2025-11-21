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

    int n, k;
    cin >> n >> k;

    vector<int> a(n * k);

    if (n == 1) {
        for (int i = 0; i < k; ++i) {
            a[i] = 1;
        }
        output_vector(a, false);
        return 0;
    }

    if (n % 2 == 0) {
        a[0] = n / 2;
        int index = 1;
        for (int i = n; i > 0; --i) {
            for (int j = 0; j < k; ++j) {
                if (i == n / 2 && j == 0) {
                    continue;
                }
                a[index] = i;
                index++;
            }   
        }
        output_vector(a, false);
        return 0;
    }
    else {
        for (int i = 0; i < k; ++i) {
            a[i] = n / 2 + 1;
        }

        a[k] = n / 2;
        int index = k + 1;
        for (int i = n; i > 0; --i) {
            if (i == n / 2 + 1) {
                continue;
            }
            for (int j = 0; j < k; ++j) {
                if (i == n / 2 && j == 0) {
                    continue;
                }
                a[index] = i;
                index++;
            }
        }
        output_vector(a, false);
        return 0;
    }

    return 0;
}
