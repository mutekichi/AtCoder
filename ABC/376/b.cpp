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

    int n, q;
    cin >> n >> q;

    int left = 0;
    int right = 1;

    int count = 0;

    for (int i = 0; i < q; ++i) {
        char h;
        int t;
        cin >> h >> t;
        t--;
        if ((left < t && t < right) || (t < right && right < left) || (right < left && left < t)) {
            if (h == 'L') {
                count += (t + n - left) % n;
                left = t;
            }
            else {
                count += (right + n - t) % n;
                right = t;
            }
        } else {
            if (h == 'L') {
                count += (left + n - t) % n;
                left = t;
            }
            else {
                count += (t + n - right) % n;
                right = t;
            }
        }
    }

    cout << count << endl;

    return 0;
}
