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
    for (int i = 0; i < v.size(); i++) {
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

int main() {

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, long long>>> g(n);

    for (int i = 0; i < m; ++i) {
        int from, to;
        long long cost;
        cin >> from >> to >> cost;
        --from; --to;
        g[from].push_back({to, cost});
        g[to].push_back({from, -cost});
    }

    vector<long long> dist(n, LLONG_MAX);

    for (int i = 0; i < n; ++i) {
        if (dist[i] != LLONG_MAX) {
            continue;
        }

        queue<int> q;
        q.push(i);
        dist[i] = 0;

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (auto [to, cost] : g[v]) {
                if (dist[to] == LLONG_MAX) {
                    dist[to] = dist[v] + cost;
                    q.push(to);
                }
                else {
                    if (dist[to] != dist[v] + cost) {
                        cout << "No" << endl;
                        return 0;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        dbgcout << dist[i] << " ";
    }

    return 0;
}
