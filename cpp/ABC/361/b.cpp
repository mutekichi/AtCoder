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

    int a, b, c, d, e, f;
    int g, h, i, j, k, l;

    cin >> a >> b >> c >> d >> e >> f;
    cin >> g >> h >> i >> j >> k >> l;

    bool ok = true;

    if ((a <= g && g < d) || (g <= a && a < j)) {
        ok = true;
    } else {
        cout << "No" << endl;
        return 0;
    }

    if ((b <= h && h < e) || (h <= b && b < k)) {
        ok = true;
    } else {
        cout << "No" << endl;
        return 0;
    }

    if ((c <= i && i < f) || (i <= c && c < l)) {
        ok = true;
    }else {
        cout << "No" << endl;
        return 0;
    }

    cout << "Yes" << endl;
    
    return 0;
}
