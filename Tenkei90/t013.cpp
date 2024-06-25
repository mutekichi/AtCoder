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



using node = int;
using edge = node;
using edge_weight = long long;

using weighted_graph = vector<vector<pair<node, edge_weight>>>;

const edge_weight INF = 1LL << 60;

weighted_graph create_weighted_graph(node n, edge m, bool zero_indexed = true) {
    
    node start, end;
    edge_weight weight;
    
    weighted_graph G(n);
    
    for (int i = 0; i < m; ++i) {
        cin >> start >> end;
        cin >> weight;
        if (zero_indexed) {
            start--; end--;
        }
        G[start].push_back(make_pair(end, weight));
        G[end].push_back(make_pair(start, weight));
    }

    return G;
}

void dijkstra_multi_ends(weighted_graph &G, node start, vector<edge_weight> &distances) {

    if (distances.size() != G.size()) {
        cout << "distances.size() must be equal to G.size()" << endl;
        exit(1);
    }

    node node_num = G.size();
    vector<edge_weight> __distances(node_num, INF);

    priority_queue<pair<edge_weight, node>, vector<pair<edge_weight, node>>, greater<pair<edge_weight, node>>> nodes_to_search;

    nodes_to_search.push(make_pair(0, start));

    while(!nodes_to_search.empty()) {
        pair<edge_weight, edge> current_node = nodes_to_search.top();
        nodes_to_search.pop();
        if (__distances[current_node.second] == INF) {
            __distances[current_node.second] = current_node.first;
            for (const auto &next_node : G[current_node.second]) {
                nodes_to_search.push(make_pair(current_node.first + next_node.second, next_node.first));
            }
        } else continue;
    }

    for (int i = 0; i < node_num; ++i) {
        distances[i] = __distances[i];
    }
}

int main() {

    node n;
    edge m;

    cin >> n >> m;

    weighted_graph G = create_weighted_graph(n, m, true);

    vector<edge_weight> distances_from_zero(n, INF);
    vector<edge_weight> distances_to_n_minus_one(n, INF);

    dijkstra_multi_ends(G, 0, distances_from_zero);
    dijkstra_multi_ends(G, n - 1, distances_to_n_minus_one);

    for (int i = 0; i < n; ++i) {
        cout << distances_from_zero[i] + distances_to_n_minus_one[i] << endl;
    }
    
    return 0;
}