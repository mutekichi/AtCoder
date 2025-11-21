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

const int MAXN = 20010; // ノードの最大数
vector<vector<pair<int, long long>>> adj; // 隣接リスト (node, weight)
vector<bool> visited;

// 重み付き木を構築
void addEdge(int u, int v, long long w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

// DFSを使って最も重い経路を見つける
pair<long long, int> dfs(int u) {
    visited[u] = true;
    pair<long long, int> maxPath = {0, u}; // (最大コスト, 終点ノード)
    for (auto p : adj[u]) {
        int v = p.first;
        long long w = p.second;
        if (!visited[v]) {
            pair<long long, int> path = dfs(v);
            path.first += w;
            if (path.first > maxPath.first) {
                maxPath = path;
            }
        }
    }
    return maxPath;
}

long long findMaxCostPath(int n) {
    fill(visited.begin(), visited.end(), false);
    pair<long long, int> farthest = dfs(0); // 任意の始点から最も遠い点を見つける

    fill(visited.begin(), visited.end(), false);
    pair<long long, int> maxPath = dfs(farthest.second); // その点から最も遠い点を見つける

    return maxPath.first; // 最大コストを返す
}


int main() {

    int n;
    cin >> n;

    long long cost_sum = 0ll;

    adj.resize(n);
    visited.resize(n, false);
    
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        addEdge(u - 1, v - 1, w);
        cost_sum += w;
    }

    long long maxCost = findMaxCostPath(n);
    
    cout << cost_sum * 2ll - maxCost << endl;

    return 0;
}
