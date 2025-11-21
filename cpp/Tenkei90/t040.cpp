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

class DirectedWeightedGraph {
public:
    struct Edge {
        int from;
        int to;
        long long weight;
        int rev;
    };

    DirectedWeightedGraph(int n) {
        this->n = n;
        this->edges.resize(n);
    }

    void add_edge(int from, int to, long long weight) {
        edges[from].push_back({from, to, weight, (int)edges[to].size()});
        edges[to].push_back({to, from, 0, (int)edges[from].size() - 1});
    }

    vector<Edge> get_edges(int from) {
        return edges[from];
    }

    /**
     * @brief Dinic's algorithm O(V^2 E)
     * 
     * @param s source
     * @param t sink
     * @return max flow
    */
    long long max_flow(int s, int t) {
        long long flow = 0;
        while (true) {
            vector<long long> dist(n, INF);
            dist[s] = 0;
            queue<int> que;
            que.push(s);
            vector<int> iter(n, 0);
            while (!que.empty()) {
                int v = que.front();
                que.pop();
                for (Edge &e : edges[v]) {
                    if (e.weight > 0 && dist[e.to] == INF) {
                        dist[e.to] = dist[v] + 1;
                        que.push(e.to);
                    }
                }
            }
            if (dist[t] == INF) {
                break;
            }
            long long f = 0;
            while ((f = dfs(s, t, INF, dist, iter)) > 0) {
                flow += f;
            }
        }
        return flow;
    }

    long long min_cut(int a, int b) {
        return max_flow(a, b);
    }

private:
    int n;
    vector<vector<Edge>> edges;
    const long long INF = numeric_limits<long long>::max();

    long long dfs(int v, int t, long long f, vector<long long> &dist, vector<int> &iter) {
        if (v == t) {
            return f;
        }
        for (int &i = iter[v]; i < edges[v].size(); i++) {
            Edge &e = edges[v][i];
            if (e.weight > 0 && dist[v] < dist[e.to]) {
                long long d = dfs(e.to, t, min(f, e.weight), dist, iter);
                if (d > 0) {
                    e.weight -= d;
                    edges[e.to][e.rev].weight += d;
                    return d;
                }
            }
        }
        return 0;
    }
};

int main() {

    int n, w;
    cin >> n >> w;

    DirectedWeightedGraph G(n + 2);

    long long max_get = 0;


    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        G.add_edge(i, n + 1, a);
        max_get += a;
    }
    

    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int c;
            cin >> c;
            G.add_edge(i, c, 1<<30);
        }
    }
    

    for (int i = 1; i <= n; ++i) {
        G.add_edge(0, i, w);
    }

    long long max_payment = G.min_cut(0, n + 1);
    

    cout << max_get - max_payment << endl;
    
    return 0;
}