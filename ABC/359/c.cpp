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

debug_cout dbgcout(true);

int main() {

    long long sx, sy, tx, ty;

    cin >> sx >> sy >> tx >> ty;

    if (sx > tx) {
        swap(sx, tx);
        swap(sy, ty);
    }
    
    if ((sx + sy) % 2 == 0) {
        sx += 1ll;
    }

    if ((tx + ty) % 2 == 0) {
        tx += 1ll;
    }

    if (abs(sx - tx) < abs(sy - ty)) {
        cout << abs(sy - ty) << endl;
    }

    else {
        cout << abs(sy - ty) + (abs(sx - tx) - abs(sy - ty)) / 2ll << endl;
    }




    
    return 0;
}