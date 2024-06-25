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

long long pow(long long n, long long p) {
    if (p == 0) return 1;
    else return pow(n, p - 1) * n;
}

bool comp_base_k (long long n1, long long n2, long long base) {
    while (n1 > 0 || n2 > 0) {
        // cout << n1 % base << " " << n2 % base << endl;
        if (n1 % base > n2 % base) return false;
        n1 /= base;
        n2 /= base; 
    }
    return true;
}

long long sum_base_k_without_overflow(long long n1, long long n2, long long base) {
    long long sum = 0;
    long long digit = 0;
    while (n1 > 0 || n2 > 0) {
        long long sum_temp = n1 % base + n2 % base;
        if (sum_temp >= base) sum_temp = base - 1;
        sum += sum_temp * pow(base, digit);
        n1 /= base;
        n2 /= base;
        ++digit;
    }
    return sum;
}

int main() {
    long long kaihatsuan_num;
    long long param_num, param_target;

    cin >> kaihatsuan_num >> param_num >> param_target;

    dbgcout << pow(param_target + 1, param_num) << endl;
    vector<vector<long long>> dp(kaihatsuan_num + 1, vector<long long>(pow(param_target + 1, param_num), LONG_MAX));
    dbgcout << "fugafuga" << endl;

    dp[0][0] = 0;
    dbgcout << "hi";

    for (long long i = 1; i <= kaihatsuan_num; ++i) {
        long long cost;
        cin >> cost;

        dbgcout << "1" << endl;
        
        long long param = 0;

        for (long long j = 0; j < param_num; ++j) {
            long long param_temp;
            cin >> param_temp;
            param = param * (param_target + 1) + param_temp;
        }

        for (long long j = 0; j < pow(param_target + 1, param_num); ++j) {
            dp[i][j] = min(dp[i][j], dp[i - 1][j]);
            if (dp[i - 1][j] == LONG_MAX) continue;
            dp[i][sum_base_k_without_overflow(j, param, param_target + 1)] = min(min(dp[i - 1][sum_base_k_without_overflow(j, param, param_target + 1)], dp[i - 1][j] + cost), dp[i][sum_base_k_without_overflow(j, param, param_target + 1)]);
        }
    }

    if (dp[kaihatsuan_num][pow(param_target + 1, param_num) - 1] == LONG_MAX) cout << -1 << endl;
    else cout << dp[kaihatsuan_num][pow(param_target + 1, param_num) - 1] << endl;

    return 0;
}