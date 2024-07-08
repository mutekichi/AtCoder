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

long long power(long long x, int n, long long maximum = 2000000000000000000ll) {
    long long res = 1ll;

    for (int i = 0; i < n; i++) {
        double dres = (double)res;
        if (dres * x > (double)maximum) return maximum;
        else res *= x;
    }

    return res;
}


// return largest m such that m ^ k <= n
long long largestM(long long n, int k) {
    
    long long left = 0ll;
    long long right = 2000000000000000000ll;
    long long mid;
    
    while (right - left > 1ll) {
        mid = (left + right) / 2ll;
        if (power(mid, k) <= n) {
            left = mid;
        } else {
            right = mid;
        }
    }

    left++;

    if (power(left, k) > n) left--;
    if (power(left, k) > n) left--;

    return left;
}



bool is_prime(long long n) {
    if (n == 1ll) {
        return false;
    }

    for (long long i = 2ll; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

vector<long long> prime_factors(long long n) {
    vector<long long> res;
    for (long long i = 2ll; i * i <= n; i++) {
        while (n % i == 0ll) {
            res.push_back(i);
            n /= i;
        }
    }
    if (n != 1ll) {
        res.push_back(n);
    }
    return res;
}

template<typename Tprime>
vector<pair<Tprime, int>> prime_factorize(Tprime n) {
    vector<pair<Tprime, int>> res;
    for (Tprime i = 2ll; i * i <= n; i++) {
        int count = 0;
        while (n % i == 0ll) {
            count++;
            n /= i;
        }
        if (count > 0) {
            res.push_back(make_pair(i, count));
        }
    }
    if (n != 1ll) {
        res.push_back(make_pair(n, 1));
    }
    return res;
}

bool is_odd(long long n) {
    return n % 2ll == 1ll;
}

bool is_even(long long n) {
    return n % 2ll == 0ll;
}

long long gcd(long long a, long long b) {
    if (b == 0ll) {
        return a;
    }
    return gcd(b, a % b);
}

void solve_naive(long long n) {
    int ans = 0;
    vector<int> good_nums;

    good_nums.push_back(1);
    ans++;

    for (long long i = 2ll; i <= n; i++) {
        auto pf = prime_factorize<long long>(i);
        if (pf.size() == 1 && pf[0].second > 1) {
            ans++;
            good_nums.push_back(i);
        } else {
            vector<int> pows;
            for (auto p : pf) {
                pows.push_back(p.second);
            }
            int __gcd = pows[0];
            for (auto p: pows) {
                __gcd = gcd(__gcd, p);
            }
            if (__gcd > 1) {
                ans++;
                good_nums.push_back(i);
            }
        }
    }

    print_vector<int>(good_nums);
    cout << ans << endl;
}

// not AC

int main() {

    long long n;
    cin >> n;

    // solve_naive(n);

    long long ans = 0ll;

    vector<long long> prime_factors;

    dbgcout << setfill(' ');
    
    for (int i = 2; i < 65; ++i) {
        if (power(2ll, i) > n) break;

        long long m = largestM(n, i);
        m--;

        vector<pair<long long, int>> pf = prime_factorize<long long>(i);

        if (pf.size() == 1 && pf[0].second == 1) {
            ans += m;
            dbgcout << "i: " << setw(4) << i << " m: " << setw(10) << m << " ans: " << setw(10) << ans << endl;
        }
        else if (pf.size() == 2) if (pf[0].second == 1 && pf[1].second == 1) {
            ans -= m;
            dbgcout << "i: " << setw(4) << i << " m: " << setw(10) << m << " ans: " << setw(10) << ans << endl;
        }
        else if (pf.size() == 3) if (pf[0].second == 1 && pf[1].second == 1 && pf[2].second == 1) {
            ans += m;
            dbgcout << "i: " << setw(4) << i << " m: " << setw(10) << m << " ans: " << setw(10) << ans << endl;
        }
        else {
            dbgcout << "i: " << i << " m: " << m << endl;
            cout << "error" << endl;
        }
    }

    cout << ans + 1 << endl;
    
    return 0;
}
