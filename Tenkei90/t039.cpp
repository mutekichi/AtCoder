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

long long dfs(
    long long prev_node,
    long long current_node,
    vector<vector<long long>>& undirected_graph,
    vector<long long>& subordinates
) {
    
    long long subordinates_count = 0ll;
    for (long long next_node : undirected_graph[current_node]) {
        if (next_node == prev_node) {
            continue;
        }
        subordinates_count += dfs(current_node, next_node, undirected_graph, subordinates) + 1ll;
    }
    subordinates[current_node] = subordinates_count;
    return subordinates[current_node];
}

int main() {

    long long n;
    cin >> n;

    long long ans = 0ll;

    vector<vector<long long>> undirected_graph(n);
    vector<pair<int, int>> edges(n - 1);

    for (long long i = 0; i < n - 1; ++i) {
        long long a, b;
        cin >> a >> b;
        --a;
        --b;
        undirected_graph[a].push_back(b);
        undirected_graph[b].push_back(a);
        edges[i] = make_pair(a, b);
    }

    vector<long long> subordinates(n, 0ll);

    dfs(-1, 0, undirected_graph, subordinates);

    for (long long i = 0; i < n - 1; ++i) {
        long long a = edges[i].first;
        long long b = edges[i].second;
        ans += (min(subordinates[a], subordinates[b]) + 1) * (n - min(subordinates[a], subordinates[b]) - 1ll);
    }
    cout << ans << endl;
        
    return 0;
}