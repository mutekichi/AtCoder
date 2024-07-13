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

    int n, m;
    cin >> n >> m;

    vector<long long> node_weights(n);
    for (int i = 0; i < n; i++) {
        cin >> node_weights[i];
    }

    vector<vector<pair<long long, int>>> edges(n);
    for (int i = 0; i < m; ++i) {
        int l, r;
        long long w;
        cin >> l >> r >> w;
        l--; r--;
        edges[l].push_back(make_pair(w, r));
        edges[r].push_back(make_pair(w, l));
    }

    vector<long long> min_weights(n, LLONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    int start_node = 0;
    pq.push(make_pair(0ll, start_node));

    while (!pq.empty()) {
        pair<long long, int> p = pq.top();
        pq.pop();
        long long weight = p.first + node_weights[p.second];
        int node = p.second;

        if (min_weights[node] != LLONG_MAX) {
            continue;
        }

        min_weights[node] = weight;

        for (int i = 0; i < edges[node].size(); i++) {
            int next_node = edges[node][i].second;
            long long next_weight = edges[node][i].first;
            if (min_weights[next_node] == LLONG_MAX) {
                pq.push(make_pair(weight + next_weight, next_node));
            }
        }
    }

    for (int i = 1; i < n; i++) {
        cout << min_weights[i];
        if (i != n - 1) cout << " ";
        else cout << endl;
    }
    
    return 0;
}
