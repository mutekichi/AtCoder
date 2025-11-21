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
    string s;
    cin >> s;

    vector<int> enemy_hands(n);
    for (int i = 0; i < n; i++) {
        if (s[i] == 'R') {
            enemy_hands[i] = 0;
        } else if (s[i] == 'S') {
            enemy_hands[i] = 1;
        } else {
            enemy_hands[i] = 2;
        }
    }

    vector<vector<int>> dp(n, vector<int>(3, 0));

    dp[0][(enemy_hands[0] + 2) % 3] = 1;
    dp[0][(enemy_hands[0] + 1) % 3] = -1;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (enemy_hands[i] == j) {
                dp[i][j] = max(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]);
            } else if (enemy_hands[i] == (j + 2) % 3) {
                dp[i][j] = -1;
            } else {
                dp[i][j] = max(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]) + 1;
            }
        }
    }

    int ans = 0;

    for (int i = 0; i < 3; ++i) {
        ans = max(ans, dp[n - 1][i]);
    }

    cout << ans << endl;
    
    return 0;
}
