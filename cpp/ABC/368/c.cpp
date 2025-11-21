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

    int n;
    cin >> n;

    long long cnt = 0ll;
    long long h;
    for (int i = 0; i < n; ++i) {
        cin >> h;
        if (cnt % 3ll == 1ll) {
            if (h == 1) {
                cnt = cnt + 1ll;
                h = h - 1ll;
            } else if (1 < h && h <= 4) {
                cnt = cnt + 2ll;
                h = h - 4ll;
            } else {
                cnt = cnt + 2ll;
                h = h - 4ll;
            }
        } else if (cnt % 3ll == 2ll) {
            if (h <= 3) {
                cnt = cnt + 1ll;
                h = h - 3ll;
            } else {
                cnt = cnt + 1ll;
                h = h - 3ll;
            }
        }
        if (h >= 0) {
            long long p = h / 5ll;
            long long m = h % 5ll;
            cnt += p * 3ll;
            if (m == 1) cnt += 1ll;
            else if (m == 2) cnt += 2ll;
            else if (m == 3 || m == 4) cnt += 3ll;
            else if (m == 0) cnt += 0ll;
        }

        // dbgcout << "cnt: " << cnt << endl;
    }

    cout << cnt << endl;

    return 0;
}
