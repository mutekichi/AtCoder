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

const int MAXN = 10000; // ノードの最大数
vector<pair<int, long long>> adj[MAXN]; // 隣接リスト (node, weight)
bool visited[MAXN];

// 重み付き木を構築
void addEdge(int u, int v, long long w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

// DFSを使って最も重い経路を見つける
pair<long long, int> dfs(int u) {
    visited[u] = true;
    pair<long long, int> maxPath = {0, u}; // (最大コスト, 終点ノード)
    for (auto& [v, w] : adj[u]) {
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
    memset(visited, false, sizeof(visited));
    pair<long long, int> farthest = dfs(0); // 任意の始点から最も遠い点を見つける

    memset(visited, false, sizeof(visited));
    pair<long long, int> maxPath = dfs(farthest.second); // その点から最も遠い点を見つける

    return maxPath.first; // 最大コストを返す
}


int main() {

    int n;
    cin >> n;
    
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        addEdge(u - 1, v - 1, w);
    }

    long long maxCost = findMaxCostPath(n);
    
    cout << maxCost << endl;

    return 0;
}
