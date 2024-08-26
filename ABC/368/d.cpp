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

    int n, k;
    cin >> n >> k;

    vector<vector<int>> graph(n);
    set<int> to_be_included;

    vector<int> valencies(n, 0);

    set<int> v_is_1_set;

    set<int> removed_nodes;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
        valencies[a]++;
        valencies[b]++;
    }

    for (int i = 0; i < k; ++i) {
        int v;
        cin >> v;
        v--;
        to_be_included.insert(v);
    }

    for (int i = 0; i < n; ++i) {
        if (valencies[i] == 1) {
            v_is_1_set.insert(i);
        }
    }

    while (!v_is_1_set.empty()) {
        int v = *v_is_1_set.begin();
        v_is_1_set.erase(v);
        if (to_be_included.find(v) != to_be_included.end()) {
            continue;
        }
        
        for (int i = 0; i < graph[v].size(); ++i) {
            int u = graph[v][i];
            valencies[u]--;
            if (valencies[u] == 1) {
                v_is_1_set.insert(u);
            }
        }
        removed_nodes.insert(v);
    }

    cout << n - removed_nodes.size() << endl;


    return 0;
}
