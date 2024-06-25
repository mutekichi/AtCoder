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

debug_cout dbgcout(false);


const int MAX_NUM = 1000010;

int main() {

    int n;
    cin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; ++i) cin >> a[i];

    sort(a.begin(), a.end());

    long long ans = 0;

    vector<long long> nums(MAX_NUM, 0);
    vector<long long> accumulated_nums(MAX_NUM, 0);

    for (int i = 0; i < n; ++i) {
        nums[a[i]]++;
    }
    for (int i = 1; i < MAX_NUM; ++i) {
        accumulated_nums[i] = accumulated_nums[i - 1] + nums[i];
    }
    
    auto unique_itr = unique(a.begin(), a.end());
    a.erase(unique_itr, a.end());

    for (int i = 0; i < a.size() - 1; ++i) {
        if (a[i + 1] / a[i] > 1) ans += nums[a[i]] * (nums[a[i]] - 1ll) / 2ll;
        for (int j = a[i + 1] / a[i]; j <= a[a.size() - 1] / a[i]; ++j) {
            int counts = accumulated_nums[min(MAX_NUM - 1ll, (j + 1ll) * a[i] - 1ll)] - accumulated_nums[j * a[i] - 1ll];
            if (j == 1) {
                dbgcout << "a[i]: " << a[i] << " " << "j: " << j << ", counts: " << counts << endl;
                ans += (counts * 2ll - nums[a[i]] - 1ll) * nums[a[i]] / 2ll;
            } else {
                dbgcout << "a[i]: " << a[i] << " " << "j: " << j << ", counts: " << counts << endl;
                ans += counts * j * nums[a[i]];
            }
        }
    }
    ans += nums[a[a.size() - 1ll]] * (nums[a[a.size() - 1ll]] - 1ll) / 2ll;

    cout << ans << endl;
    
    return 0;
}