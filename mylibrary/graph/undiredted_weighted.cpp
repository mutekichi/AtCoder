#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>



using namespace std;
const long long INF = 1LL << 60;

/**
 * @brief UnionFind usage: UnionFind uf(n);
 * 
*/
class UnionFind {
public:
    // parent[i] = j: i's parent is j. if parent[i] = i, i is root
    vector<int> parent;
    // rank[i] = j: the depth of the tree whose root is i. if rank[i] = 0, i is leaf
    vector<int> rank;
    // size[i] = j: the size of the tree whose root is i
    vector<int> size;

    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n);
        size.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
            size[i] = 1;
        }
    }

    // return the root of the tree to which x belongs
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    // unite the tree to which x belongs and the tree to which y belongs
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (rank[x] < rank[y]) {
            parent[x] = y;
            size[y] += size[x];
        } else {
            parent[y] = x;
            size[x] += size[y];
            if (rank[x] == rank[y]) rank[x]++;
        }
    }

    // return whether x and y belong to the same tree
    bool same(int x, int y) {
        return find(x) == find(y);
    }

    // return the size of the tree to which x belongs
    int get_size(int x) {
        return size[find(x)];
    }
};

/**
 * @brief WeightedGraph usage: WeightedGraph<int, long long> G(n);
 * 
 * @tparam TNode The type of the nodes in the graph.
 * @tparam TEdge The type of the weights of the edges.
 * 
 */
template<typename TNode, typename TEdge>
class WeightedGraph {
public:
    struct Edge {
        TNode from;
        TNode to;
        TEdge weight;
    };

    TNode node_num;
    vector<vector<pair<TNode, TEdge>>> edges;

    WeightedGraph(TNode node_num) {
        this->node_num = node_num;
        this->edges.resize(node_num);
    }

    void add_edge(TNode from, TNode to, TEdge weight) {
        edges[from].push_back(make_pair(to, weight));
        edges[to].push_back(make_pair(from, weight));
    }

    vector<pair<TNode, TEdge>> get_edges(TNode from) {
        return edges[from];
    }
    
    void print_edges() {
        for (TNode i = 0; i < node_num; ++i) {
            cout << i << ": ";
            for (const auto &edge : edges[i]) {
                cout << "(" << edge.first << ", " << edge.second << ") ";
            }
            cout << endl;
        }
    }

    /**
     * @brief Erase self loops
     * 
     */
    void erase_self_loops() {
        for (TNode i = 0; i < node_num; ++i) {
            for (int j = 0; j < edges[i].size(); ++j) {
                if (edges[i][j].first == i) {
                    edges[i].erase(edges[i].begin() + j);
                    break;
                }
            }
        }
    }

    /**
     * @brief Erase parallel edges
     * 
     * @param comp a function that compares two edges
     * @return void
     * 
     * @note O(E log E)
     * 
     * @example G.erase_parallel_edges([](TEdge a, TEdge b) { return a < b; });
     */
    void erase_parallel_edges(function<bool(TEdge, TEdge)> comp) {
        for (TNode i = 0; i < node_num; ++i) {
            sort(edges[i].begin(), edges[i].end());
            edges[i].erase(unique(edges[i].begin(), edges[i].end(), [&](pair<TNode, TEdge> a, pair<TNode, TEdge> b) {
                return a.first == b.first && comp(a.second, b.second);
            }), edges[i].end());
        }
    }
    
    /**
     * @brief Find the shortest path from start to all nodes
     * 
     * @param start
     * @param distances
     * @return void
     * 
     * @note O(E log V)
     */
    void find_shortest_path(TNode start, vector<TEdge> &distances) {
        dijkstra_multi_ends(start, distances);
    }

    /**
     * @brief Find the minimum spanning tree
     * 
     * @param start
     * @param minimum_spanning_tree
     * @return TEdge
     * 
     * @note O(E log V)
     */
    TEdge find_minimum_spanning_tree(vector<Edge> &minimum_spanning_tree) {
        TEdge minimum_cost = kruskal(minimum_spanning_tree);
        return minimum_cost;
    }
    TEdge find_minimum_spanning_tree() {
        vector<Edge> minimum_spanning_tree;
        TEdge minimum_cost = kruskal(minimum_spanning_tree);
        return minimum_cost;
    }

private: 
    
    void dijkstra_multi_ends(TNode start, vector<TEdge> &distances) {
        
        if (distances.size() != node_num) {
            cout << "distances.size() must be equal to G.size()" << endl;
            exit(1);
        }

        vector<TEdge> __distances(node_num, INF);

        priority_queue<pair<TEdge, TNode>, vector<pair<TEdge, TNode>>, greater<pair<TEdge, TNode>>> nodes_to_search;

        nodes_to_search.push(make_pair(0, start));

        while(!nodes_to_search.empty()) {
            pair<TEdge, TNode> current_node = nodes_to_search.top();
            nodes_to_search.pop();
            if (__distances[current_node.second] == INF) {
                __distances[current_node.second] = current_node.first;
                for (const auto &next_node : edges[current_node.second]) {
                    nodes_to_search.push(make_pair(current_node.first + next_node.second, next_node.first));
                }
            } else continue;
        }

        for (int i = 0; i < node_num; ++i) {
            distances[i] = __distances[i];
        }
    }

    TEdge kruskal( vector<Edge> &minimum_spanning_tree) {
        vector<Edge> all_edges;
        for (TNode i = 0; i < node_num; ++i) {
            for (const auto &edge : edges[i]) {
                if (i < edge.first) {
                    all_edges.push_back({i, edge.first, edge.second});
                }
            }
        }
        sort(all_edges.begin(), all_edges.end(), [](const Edge &a, const Edge &b) {
            return a.weight < b.weight;
        });

        UnionFind uf(node_num);

        TEdge minimum_cost = 0;

        for (const auto &edge : all_edges) {
            if (!uf.same(edge.from, edge.to)) {
                uf.unite(edge.from, edge.to);
                minimum_cost += edge.weight;
                minimum_spanning_tree.push_back(edge);
            }
        }

        if (minimum_spanning_tree.size() != node_num - 1) {
            return -1;
        }

        return minimum_cost;
    }
    
};
