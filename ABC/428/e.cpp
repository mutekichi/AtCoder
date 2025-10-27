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

class debug_cout
{
public:
    debug_cout(bool debug) : debug(debug) {}

    template <typename T>
    debug_cout &operator<<(const T &value)
    {
        if (debug)
        {
            cout << value;
        }
        return *this;
    }

    debug_cout &operator<<(std::ostream &(*manip)(std::ostream &))
    {
        if (debug)
        {
            manip(std::cout);
        }
        return *this;
    }

private:
    bool debug;
};

debug_cout dbgcout(true);

template <typename T>
void output_vector(vector<T> v, bool debug)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (debug)
        {
            dbgcout << v[i] << " ";
        }
        else
        {
            cout << v[i] << " ";
        }
    }
    if (debug)
    {
        dbgcout << endl;
    }
    else
    {
        cout << endl;
    }
}

class Tree
{
public:
    Tree(int n) : n(n)
    {
        tree.resize(n);
        sz.resize(n);
    }

    void add_edge(int u, int v)
    {
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    vector<vector<int>> tree;
    int n;

    /**
     * @brief Find the centroids of a tree O(V)
     *
     * @return vector<int> centroids
     * @note one or two centroids
     */
    vector<int> find_centroids()
    {
        vector<int> centroid;
        dfs_centroids(0, -1, centroid);
        return centroid;
    }

    /**
     * @brief Find the diameter of a tree O(V)
     *
     * @return pair<int: diameter, pair<int: node1, int: node2>>
     */
    pair<int, pair<int, int>> diameter()
    {
        vector<int> dist(n, 0);
        int farthest_node = 0;
        int farthest_node_distance = 0;
        dfs_diameter(0, -1, dist, farthest_node, farthest_node_distance);

        vector<int> dist2(n, 0);
        int farthest_node2 = farthest_node;
        int farthest_node_distance2 = 0;
        dfs_diameter(farthest_node, -1, dist2, farthest_node2, farthest_node_distance2);

        return make_pair(farthest_node_distance2, make_pair(farthest_node, farthest_node2));
    }

    int diameter_length()
    {
        return diameter().first;
    }

    pair<int, int> diameter_nodes()
    {
        return diameter().second;
    }

private:
    void dfs_diameter(int node, int parent, vector<int> &dist, int &farthest_node, int &farthest_node_distance)
    {
        for (int next_node : tree[node])
        {
            if (next_node == parent)
                continue;
            dist[next_node] = dist[node] + 1;
            if (dist[next_node] > farthest_node_distance)
            {
                farthest_node = next_node;
                farthest_node_distance = dist[next_node];
            }
            dfs_diameter(next_node, node, dist, farthest_node, farthest_node_distance);
        }
    }

    void dfs_centroids(int u, int prev, vector<int> &centroid)
    {
        sz[u] = 1;
        bool is_centroid = true;
        for (auto v : tree[u])
        {
            if (v != prev)
            {
                dfs_centroids(v, u, centroid);
                sz[u] += sz[v];
                if (sz[v] > n / 2)
                    is_centroid = false;
            }
        }
        if (n - sz[u] > n / 2)
            is_centroid = false;
        if (is_centroid)
            centroid.push_back(u);
    }

    vector<int> sz;
};

int main()
{
    int n;
    cin >> n;

    Tree t(n);

    for (int i = 0; i < n; ++i)
    {
        int a, b;
        t.add_edge(--a, --b);
    }

    int center = t.find_centroids()[0];

    int nums = t.tree[center].size();

    vector<int> v_sets(nums);

    

    return 0;
}
