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

vector<pair<long long, int>> prime_factorization(long long n) {
    vector<pair<long long, int>> res;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i != 0) {
            continue;
        }
        int count = 0;
        while (n % i == 0) {
            n /= i;
            count++;
        }
        res.push_back(make_pair(i, count));
    }
    if (n != 1) {
        res.push_back(make_pair(n, 1));
    }
    return res;
}

vector<long long> factors(long long n) {
    vector<long long> res;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i != 0) {
            continue;
        }
        res.push_back(i);
        if (i * i != n) {
            res.push_back(n / i);
        }
    }
    return res;
}

// reverse(123) = 321
long long reverse(long long n) {
    long long res = 0;
    while (n > 0) {
        res = res * 10 + n % 10;
        n /= 10;
    }
    return res;
}

// includes_zero(123) = false
// includes_zero(120) = true
bool includes_zero(long long n) {
    while (n > 0) {
        if (n % 10 == 0) {
            return true;
        }
        n /= 10;
    }
    return false;

}

map<long long, string> memo;

string f(long long n) {
    if (memo.find(n) != memo.end()) {
        return memo[n];
    }
    if (!includes_zero(n) && n == reverse(n)) {
        memo[n] = to_string(n);
        return to_string(n);
    } else {
        for (long long i = 2; i * i <= n; ++i) {
            if (n % i != 0) {
                continue;
            }
            if (includes_zero(i)) continue;
            long long rev_i = reverse(i);
            if (n % (i * rev_i) != 0) continue;
            long long mid = n / (i * rev_i);
            
            if (f(mid) == "") continue;
            else {
                string ans = to_string(i) + "*" + f(mid) + "*" + to_string(rev_i);
                memo[n] = ans;
                return ans;
            }
        }
    }
    return "";
}


int main() {

    long long n;
    cin >> n;
    
    cout << (f(n) == "" ? "-1" : f(n)) << endl;
    
    return 0;
}
