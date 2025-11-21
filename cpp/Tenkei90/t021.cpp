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

void first_dfs(int node, vector<vector<int>> &directed_graph, vector<int> &pre_ordered_nodes, vector<bool> &is_seen) {
    if (is_seen[node]) return;
    
    is_seen[node] = true;
    for (const auto &next_node : directed_graph[node]) {
        first_dfs(next_node, directed_graph, pre_ordered_nodes, is_seen);
    }

    pre_ordered_nodes.push_back(node);
}

void second_dfs(
    int node,
    vector<bool> &is_seen,
    vector<vector<int>> &directed_graph,
    vector<int> &strongly_connected_components_buffer
) {
    is_seen[node] = true;
    strongly_connected_components_buffer.push_back(node);
    for(int next_node : directed_graph[node]) {
        if (!is_seen[next_node]) {
            second_dfs(next_node, is_seen, directed_graph, strongly_connected_components_buffer);
        }
    }
}

void search_strongly_connected_components(
    vector<int> &post_ordered_nodes,
    vector<vector<int>> &directed_graph,
    vector<vector<int>> &strongly_connected_components
) {
    int current_strongly_connected_component_index = 0;
    vector<int> strongly_connected_components_buffer;
    vector<bool> is_seen(directed_graph.size(), false);

    for (int node : post_ordered_nodes) {
        if (is_seen[node]) {
            continue;
        } else {
            second_dfs(node, is_seen, directed_graph, strongly_connected_components_buffer);
        }
        strongly_connected_components.push_back(strongly_connected_components_buffer);
        strongly_connected_components_buffer.clear();
    }

}

void get_strongly_connected_components(
    vector<vector<int>> &directed_graph,
    vector<vector<int>> &strongly_connected_components
) {
    int n = directed_graph.size();

    vector<vector<int>> reversed_directed_graph(n);
    for (int from = 0; from < n; ++from) {
        for (int to : directed_graph[from]) {
            reversed_directed_graph[to].push_back(from);
        }
    }

    vector<int> pre_ordered_nodes;
    vector<bool> is_seen(n, false);

    for (int node = 0; node < n; ++node) {
        first_dfs(node, directed_graph, pre_ordered_nodes, is_seen);
    }

    vector<int> post_ordered_nodes(pre_ordered_nodes.rbegin(), pre_ordered_nodes.rend());

    search_strongly_connected_components(post_ordered_nodes, reversed_directed_graph, strongly_connected_components);
}

int main() {

    int n, m;
    cin >> n >> m;

    vector<vector<int>> directed_graph(n);

    int a, b;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        a--; b--;
        directed_graph[a].push_back(b);
    }

    vector<vector<int>> strongly_connected_components;

    get_strongly_connected_components(directed_graph, strongly_connected_components);

    long long cnt = 0;

    for (auto strongly_connected_component : strongly_connected_components) {
        long long size = strongly_connected_component.size();
        cnt += size * (size - 1ll) / 2ll; 
    }

    cout << cnt << endl;

    return 0;
}