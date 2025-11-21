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


class union_find {
    public:
        // parent[i] = j: i's parent is j. if parent[i] = i, i is root
        vector<int> parent;
        // rank[i] = j: the depth of the tree whose root is i. if rank[i] = 0, i is leaf
        vector<int> rank;
        // size[i] = j: the size of the tree whose root is i
        vector<int> size;

        union_find(int n) {
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

class debug {
    int n = 0;
    public:
        void count() {
            // cout << "debug" << ++n << " ";
        };
        void print(string s) {
            cout << s << endl;
        };
        void clear() {
            n = 0;
            // cout << endl;
        };
};


int main() {

    debug d;

    int n, m;
    cin >> n >> m;

    set<tuple<int, int, int>> edge_set;

    int k, c;
    int a0;
    int aj;

    for (int i = 0; i < m; ++i) {
        cin >> k >> c;
        for (int j = 0; j < k; ++j) {
            if (j == 0) {
                cin >> a0;
            } else {
                cin >> aj;
                edge_set.insert(make_tuple(c, a0 - 1, aj - 1));
            }
        }
    }
    long long cost = 0;
    union_find uf(n);
    
    while(edge_set.empty() == false) {
        d.count();
        auto edge = *edge_set.begin();
        edge_set.erase(edge);

        int c = get<0>(edge);
        int node_start = get<1>(edge);
        int node_end = get<2>(edge);

        if (uf.same(node_start, node_end)) {
            continue;
        } else {
            uf.unite(node_start, node_end);
            cost += c;
        }
        d.count();
        d.clear();
    }

    if (uf.get_size(0) != n) {
        cout << -1 << endl;
    } else {
        cout << cost << endl;
    }
    
    return 0;
}
