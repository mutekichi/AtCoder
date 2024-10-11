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

long long calc_min_cost(long long count1, long long cost1, long long count2, long long cost2, long long target_count) {
    long long total_cost = LLONG_MAX;

    int larger_count, larger_cost, smaller_count, smaller_cost;
    if (count1 > count2) {
        larger_count = count1;
        larger_cost = cost1;
        smaller_count = count2;
        smaller_cost = cost2;
    }
    else {
        larger_count = count2;
        larger_cost = cost2;
        smaller_count = count1;
        smaller_cost = cost1;
    }

    for (long long num_larger = 0; num_larger * larger_count <= target_count; num_larger++) {
        long long num_smaller = (target_count - num_larger * larger_count) / smaller_count;
        
        if (num_larger * larger_count + num_smaller * smaller_count < target_count) {
            num_smaller++;
        }

        long long cost = num_larger * larger_cost + num_smaller * smaller_cost;


        long long total_cost = min(cost, total_cost);
    }

    return total_cost;
}

bool check_achievable(long long n, long long x, vector<pair<Machine, Machine>> &machines, long long target_count) {
    long long total_cost = 0;
    for (long long i = 0; i < n; i++) {
        long long cost = calc_min_cost(machines[i].first.count, machines[i].first.cost, machines[i].second.count, machines[i].second.cost, target_count);
        total_cost += cost;
    }

    return total_cost <= x;
}

int main() {

    long long n, x;
    cin >> n >> x;

    vector<pair<Machine, Machine>> machines(n);

    for (long long i = 0; i < n; i++) {
        cin >> machines[i].first.count >> machines[i].first.cost >> machines[i].second.count >> machines[i].second.cost;
    }
    


    return 0;
}
