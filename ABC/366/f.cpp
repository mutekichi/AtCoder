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

debug_cout dbgcout(false);

struct LinearFunction {
    long long a, b;
    LinearFunction(long long a, long long b) : a(a), b(b) {}
    long long apply(long long x) const {
        return a * x + b;
    }
};

long long solve(const vector<LinearFunction>& functions, int k) {
    int n = functions.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));
    
    // 初期値：x = 1
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            // i番目の関数を選ばない場合
            dp[i][j] = dp[i-1][j];
            
            // i番目の関数を選ぶ場合
            if (j > 0) {
                long long applied = functions[i-1].apply(dp[i-1][j-1]);
                dp[i][j] = max(dp[i][j], applied);
            }
        }
    }
    
    return dp[n][k];
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<pair<long long, long long>> funcs(n);
    for (int i = 0; i < n; i++) {
        cin >> funcs[i].first >> funcs[i].second;
    }

    sort(funcs.begin(), funcs.end(), [](pair<long long, long long> a, pair<long long, long long> b) {
        return (a.first - 1) * b.second < (b.first - 1) * a.second;
    });

    for (int i = 0; i < n; i++) {
        dbgcout << funcs[i].first << " " << funcs[i].second << endl;
    }

    vector<LinearFunction> functions;
    for (int i = 0; i < n; i++) {
        functions.emplace_back(funcs[i].first, funcs[i].second);
    }

    long long ans = solve(functions, k);
    cout << ans << endl;
    return 0;
}
