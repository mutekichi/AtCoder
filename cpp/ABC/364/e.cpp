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

    int n;
    cin >> n;
    int sweet_lim, salty_lim;
    cin >> sweet_lim >> salty_lim;

    vector<pair<int, int>> sweet_salty(n);

    for (int i = 0; i < n; i++) {
        cin >> sweet_salty[i].first >> sweet_salty[i].second;
    }

    sort(sweet_salty.begin(), sweet_salty.end());

    vector<vector<vector<int>>> dp(n + 1,
            vector<vector<int>>(sweet_lim + 1,
                vector<int>(salty_lim + 1, 0)));

    vector<pair<int, int>> indices_to_check;
    indices_to_check.push_back(make_pair(0, 0));

    for (int i = 0; i < n; i++) {
        int sweet = sweet_salty[i].first;
        int salty = sweet_salty[i].second;

        for (auto p : indices_to_check) {
            int si = p.first;
            int sj = p.second;

            if (si + sweet <= sweet_lim && sj + salty <= salty_lim) {
                dp[i + 1][si + sweet][sj + salty] = max(dp[i + 1][si + sweet][sj + salty], dp[i][si][sj] + 1);
                indices_to_check.push_back(make_pair(si + sweet, sj + salty));
            }

            dp[i + 1][si][sj] = max(dp[i + 1][si][sj], dp[i][si][sj]);
        }
    }

    int ans = 0;
    for (int i = 0; i <= sweet_lim; i++) {
        for (int j = 0; j <= salty_lim; j++) {
            ans = max(ans, dp[n][i][j]);
        }
    }

    if (ans == n) cout << ans << endl;
    else cout << ans + 1 << endl;
    
    return 0;
}
