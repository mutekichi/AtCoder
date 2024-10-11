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
void print_vector(vector<T> v, bool debug) {
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

long long calc_min_cost(
    pair<Machine, Machine> machines,
    long long x
) {
    long long min_cost = LLONG_MAX;

    for (long long i = 0; i <= machine.count; i++) {
        long long cost = i * machine.cost;
        long long remain = x - i;

        if (remain < 0) {
            break;
        }

        min_cost = min(min_cost, cost + remain * machine.cost);
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
    
    long long left = -1, right = 1e8;

    while(right - left > 1) {
        long long mid = (left + right) / 2;
        long long total_cost = 0;
        for (int i = 0; i < n; ++i ) 
        {
            long long min_cost = calc_min_cost(machines[i], mid);
            total_cost += min_cost;
        }

        if (total_cost <= x) {
            right = mid;
        }
        else {
            left = mid;
        }
    }

    cout << left << endl;

    return 0;
}
