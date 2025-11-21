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

long long mod = 1000000007;

int main() {

    int n;
    cin >> n;

    string s;
    cin >> s;

    for (int i = 0; i < n; i = i + 2) {
        if (s[i] == 'A') s[i] = 'B';
        else s[i] = 'A';
    }
    long long ans = 1ll;

    long long run_length = 1ll;

    for (int i = 1; i < n; ++i) {
        if (s[i] == s[i - 1]) {
            ++run_length;
        } else {
            long long patterns = (run_length + 1ll) / 2ll;
            ans = (ans * patterns) % mod;
            run_length = 1ll;
        }
    }

    long long patterns = (run_length + 1ll) / 2ll;
    ans = (ans * patterns) % mod;

    cout << ans << endl;
    
    return 0;
}
