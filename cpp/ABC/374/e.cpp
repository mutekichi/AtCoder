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
void output_vector(vector<T> v, bool debug) {
    for (long long i = 0; i < v.size(); i++) {
        if (debug) {
            dbgcout << v[i] << " ";
        }
        else {
            cout << v[i] << " ";
        }
    }
    if (debug) {
        dbgcout << endl;
    }
    else {
        cout << endl;
    }
}

struct Machine {
    long long count, cost;
};

long long calc_cost(Machine m1, Machine m2, long long quantity) {
    long long min_cost = LLONG_MAX;

    // if m2 is "cheaper" than m1, swap them
    // so that m1 is always cheaper than m2
    if (m2.count * m1.cost > m1.count * m2.cost) {
        swap(m1, m2);
    }

    // search the number of machines 2 to buy
    // the number is proved to be less than m1.count
    for (long long i = 0; i <= m1.count; i++) {
        long long num = i * m2.count;
        long long left = quantity - num;
        long long x1_count = left / m1.count;
        if (left % m1.count != 0) {
            x1_count++;
        }
        long long cost = i * m2.cost + x1_count * m1.cost;
        min_cost = min(min_cost, cost);
    }

    return min_cost;
}

int main() {

    long long n, x;
    cin >> n >> x;

    vector<pair<Machine, Machine>> machines(n);

    for (long long i = 0; i < n; i++) {
        cin >> machines[i].first.count >> machines[i].first.cost >> machines[i].second.count >> machines[i].second.cost;
    }
    
    
    long long left = -1ll, right = (long long)1e9 + 100ll;

    while(right - left > 1) {
        long long mid = (left + right) / 2;
        long long cost = 0;
        
        for (long long i = 0; i < n; ++i) {
            cost += calc_cost(machines[i].first, machines[i].second, mid);
        }

        if (cost <= x) {
            right = mid;
        }
        else {
            left = mid;
        }
    }

    cout << right << endl;

    return 0;
}
