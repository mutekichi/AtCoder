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

int main() {

    int n, q;
    cin >> n >> q;
    
    vector<long long> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i];
    }

    sort(points.begin(), points.end());

    for (int i = 0; i < q; ++i) {
        long long x;
        int k; //find the k-th nearest point to x
        cin >> x;
        cin >> k;

        int x_index = lower_bound(points.begin(), points.end(), x) - points.begin();

        int left = x_index;
        int right = n;

        while (right - left > 1) {
            int mid = (left + right) / 2;
            long long mid_val = points[mid];
            long long oppos_val = 2 * x - mid_val;
            int oppos_index = lower_bound(points.begin(), points.end(), oppos_val) - points.begin();
            int points_between = mid - oppos_index;
            if (points_between >= k) {
                right = mid;
            } else {
                left = mid;
            }
        }

        cout << points[right - 1] - x << endl;
    }


    
    return 0;
}
