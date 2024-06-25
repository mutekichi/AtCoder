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

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {

    long long n, m;
    cin >> n >> m;
    long long k;
    cin >> k;
    
    long long left = -1ll;
    long long right = 5000000025000000000ll;

    long long lcm = n / gcd(n, m) * m;

    while(left < right) {
        long long mid = (left + right) / 2ll;
        long long count = mid / n + mid / m - mid / lcm * 2;

        if (count < k) {
            left = mid + 1ll;
        } else {
            right = mid;
        }
    }

    left--;

    while(true) {
        long long count = left / n + left / m - left / lcm * 2ll;
        if (count == k) {
            cout << left << endl;
            break;
        }
        left++;
    }

    return 0;
}
