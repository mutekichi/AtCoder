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
void print_vector(vector<T> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

// int main() {

//     long long n, t;
//     cin >> n >> t;

//     string s;
//     cin >> s;

//     vector<long long> pos;
//     vector<long long> neg;

//     vector<pair<long long, int>> vecp1;
//     vector<pair<long long, int>> vecp2;

//     long long x;

//     for (long long i = 0ll; i < n; ++i) {
//         cin >> x;
//         if (s[i] == '1') {
//             pos.push_back(x);
//             vecp1.push_back(make_pair(x, 2));
//             vecp2.push_back(make_pair(x + t, 2));
//         } else {
//             neg.push_back(x);
//             vecp1.push_back(make_pair(x, 1));
//             vecp2.push_back(make_pair(x - t, 1));
//         }
//     }

//     sort(vecp1.begin(), vecp1.end());
//     sort(vecp2.begin(), vecp2.end());

//     long long ans = 0ll;

//     long long cnt1 = 0ll;
//     for (long long i = 0ll; i < n; ++i) {
//         if (vecp1[i].second == 1) {
//             cnt1++;
//         } else {
//             ans += cnt1;
//         }
//     }

//     long long ans2 = 0ll;
//     long long cnt2 = 0ll;
//     for (long long i = 0ll; i < n; ++i) {
//         if (vecp2[i].second == 1) {
//             cnt2++;
//         } else {
//             ans2 += cnt2;
//         }
//     }

//     cout << ans2 - ans << endl;
    
//     return 0;
// }

int main() {
    int n;
    long long t;

    cin >> n >> t;

    string s;
    cin >> s;

    vector<long long> positive_ants;
    vector<long long> negative_ants;

    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;

        if (s[i] == '1') positive_ants.push_back(x);
        else negative_ants.push_back(x);
    }

    sort(positive_ants.begin(), positive_ants.end());
    sort(negative_ants.begin(), negative_ants.end());

    long long ans = 0;

    for (int i = 0; i < positive_ants.size(); ++i) {
        long long x = positive_ants[i];

        // find the first element that is greater than x
        auto it_left = lower_bound(negative_ants.begin(), negative_ants.end(), x);
        // find the last element that is less than x + 2 * t
        auto it_right = upper_bound(negative_ants.begin(), negative_ants.end(), x + 2ll * t);

        ans += distance(it_left, it_right);
    }

    cout << ans << endl;
}