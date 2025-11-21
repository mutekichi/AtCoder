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
