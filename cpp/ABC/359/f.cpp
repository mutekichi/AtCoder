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

debug_cout dbgcout(true);

long long calc_next_cost(tuple<long long, long long, long long> node) {
    return get<1>(node) * (2ll * get<2>(node) + 1ll);
}

tuple<long long, long long, long long> next_node(tuple<long long, long long, long long> re) {
    return make_tuple(calc_next_cost(re), get<1>(re), get<2>(re) + 1ll);
}

int main() {

    int n;
    cin >> n;

    vector<tuple<long long, long long, long long>> remain_node;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        remain_node.push_back(make_tuple(a, a, 1ll));
    }

    multiset<tuple<long long, long long, long long>> used_node;

    long long ans = 0;

    sort(remain_node.begin(), remain_node.end());

    used_node.insert(next_node(remain_node[0]));
    used_node.insert(next_node(remain_node[1]));

    ans += get<0>(remain_node[0]) + get<0>(remain_node[1]);

    // cout << ans << endl;
    // cout << endl;

    for (int i = 2; i < n; ++i) {
        auto min_node = *used_node.begin();
        used_node.erase(used_node.begin());
        ans += get<0>(min_node);
        // cout << ans << endl;
        used_node.insert(next_node(min_node));
        used_node.insert(next_node(remain_node[i]));
        ans += get<0>(remain_node[i]);
        // cout << ans << endl;
        // cout << endl;
    }

    cout << ans << endl;
    
    return 0;
}