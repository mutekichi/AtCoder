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

void initialize_distances(vector<int> &distances) {
    for (int i = 0; i < distances.size(); ++i) {
        distances[i] = INT_MAX;
    }
}

void dfs(vector<vector<int>> &graph, vector<int> &distances, int node) {
    for (const auto &next_node : graph[node]) {
        if (distances[node] != INT_MAX) {
            distances[next_node] = min(distances[next_node], distances[node] + 1);
            dfs(graph, distances, next_node);
        }
    }
}

void bfs(vector<vector<int>> &graph, vector<int> &distances, int node) {
    queue<int> q;
    q.push(node);
    distances[node] = 0;

    while (!q.empty()) {
        int current_node = q.front();
        q.pop();

        for (const auto &next_node : graph[current_node]) {
            if (distances[next_node] == INT_MAX) {
                distances[next_node] = distances[current_node] + 1;
                q.push(next_node);
            }
        }
    }
}

int find_farthest_node(vector<int> &distances) {
    int farthest_node = 0;
    for (int i = 0; i < distances.size(); ++i) {
        if (distances[i] > distances[farthest_node]) {
            farthest_node = i;
        }
    }
    return farthest_node;
}

void print_distances(vector<int> &distances) {
    for (int i = 0; i < distances.size(); ++i) {
        cout << distances[i] << " ";
    }
    cout << endl;
}

int main() {

    int n;
    cin >> n;

    vector<int> distances(n);
    vector<vector<int>> graph(n);

    initialize_distances(distances);

    int a, b;

    for (int i = 0; i < n - 1; ++i) {
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    bfs(graph, distances, 0);

    int farthest_node = find_farthest_node(distances);

    initialize_distances(distances);
    
    bfs(graph, distances, farthest_node);

    farthest_node = find_farthest_node(distances);

    cout << distances[farthest_node] + 1 << endl;
    
    return 0;
}