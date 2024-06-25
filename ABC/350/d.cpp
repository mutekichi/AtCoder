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


void dfs(vector<vector<long long>>& graph, vector<bool>& visited, long long start, vector<long long>& component) {
    visited[start] = true;
    component.push_back(start);
    for (long long neighbor : graph[start]) {
        if (!visited[neighbor]) {
            dfs(graph, visited, neighbor, component);
        }
    }
}

vector<vector<long long>> find_connected_components(vector<vector<long long>>& graph) {
    long long n = graph.size();
    vector<bool> visited(n, false);
    vector<vector<long long>> components;

    for (long long node = 0; node < n; ++node) {
        if (!visited[node]) {
            vector<long long> component;
            dfs(graph, visited, node, component);
            components.push_back(component);
        }
    }

    return components;
}

vector<long long> get_component_sizes(vector<vector<long long>>& components) {
    vector<long long> component_sizes;
    for (auto& component : components) {
        component_sizes.push_back(component.size());
    }
    return component_sizes;
}

int main() {

    long long n, m;

    cin >> n >> m;

    vector<vector<long long>> graph(n);
    for (long long i = 0; i < m; ++i) {
        long long a, b;
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }

    auto components = find_connected_components(graph);
    auto component_sizes = get_component_sizes(components);

    long long volume = 0;

    for (long long size : component_sizes) {
        volume += size * (size - 1) / 2;
    }

    cout << volume - m << endl;
    
    return 0;
}