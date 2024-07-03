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

int main() {

    string s;
    string t;

    cin >> s >> t;

    int lens = s.size();
    int lent = t.size();

    for (int i = 1; i < lens; ++i) {
        for (int j = 1; j <= i; ++j) {
            string u = "";
            for (int k = 0; k < lens / i; ++k) {
                u += s[k * i + j - 1];
            }
            int amari = lens % i;
            if (amari >= j) {
                u += s[lens - amari + j - 1];
            }
            if (u == t) {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }

    cout << "No" << endl;
    
    return 0;
}
