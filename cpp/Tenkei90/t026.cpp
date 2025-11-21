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
#include <cstdlib>

using namespace std;

void dfs(vector<vector<int>> &graph, int node, vector<int> &node_state, bool is_black) {
    if (node_state[node] != 0) return;
    node_state[node] = is_black ? 1 : 2;
    for (int next : graph[node]) {
        dfs(graph, next, node_state, !is_black);
    }
}

int main() {

    int n;
    cin >> n;

    vector<vector<int>> graph(n);

    int a, b;
    for (int i = 0; i < n - 1; ++i) {
        cin >> a >> b;
        --a; --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int start = 0;
    while(graph[start].size() != 1) {
        ++start;
    }

    vector<int> node_state(n, 0);

    int cnt = 0;
    dfs(graph, start, node_state, true);

    for (int i = 0; i < n; ++i) {
        if (node_state[i] == 1) ++cnt;
    }

    if (cnt <= n / 2) {
        cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (node_state[i] == 2) {
                cout << i + 1 << endl;
                ++cnt;
                if (cnt == n / 2) break;
            }
        }
    } else {
        cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (node_state[i] == 1) {
                cout << i + 1 << endl;
                ++cnt;
                if (cnt == n / 2) break;
            }
        }
    }
    
    return 0;
}