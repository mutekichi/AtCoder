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

    // directed graph
    vector<vector<int>> g(n);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
    }

    // bfs from 0
    // find the shortest path from 0 to 0

    vector<int> dist(n, -1);
    dist[0] = 0;

    queue<pair<int, int>> q;

    q.push({0, 0});

    while (!q.empty()) {
        auto [v, d] = q.front();
        q.pop();

        // dbgcout << "v: " << v << " d: " << d << endl;


        for (auto u : g[v]) {
            if (u == 0) {
                cout << d + 1 << endl;
                return 0;
            }
            if (dist[u] != -1) {
                continue;
            }
            dist[u] = d + 1;
            q.push({u, d + 1});
        }
    }

    cout << -1 << endl;

    return 0;
}
