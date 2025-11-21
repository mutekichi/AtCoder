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

int get_union_find_index(int r, int c, int width) {
    return r * width + c;
}

void run_query1(vector<vector<bool>> &board, int r, int c, int height, int width, UnionFind &union_find) {
    board[r][c] = true;
    if (c != 0 && board[r][c - 1]) union_find.unite(get_union_find_index(r, c, width), get_union_find_index(r, c - 1, width));
    if (c != width - 1 && board[r][c + 1]) union_find.unite(get_union_find_index(r, c, width), get_union_find_index(r, c + 1, width));
    if (r != 0 && board[r - 1][c]) union_find.unite(get_union_find_index(r, c, width), get_union_find_index(r - 1, c, width));
    if (r != height - 1 && board[r + 1][c]) union_find.unite(get_union_find_index(r, c, width), get_union_find_index(r + 1, c, width));
}

void run_query2(vector<vector<bool>> &board, int ra, int ca, int rb, int cb, int width, UnionFind &union_find) {
    if (ra == rb && ca == cb) {
        if (board[ra][ca]) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    else {
        if (union_find.same(get_union_find_index(ra, ca, width), get_union_find_index(rb, cb, width))) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}

int main() {

    int height, width;
    cin >> height >> width;

    vector<vector<bool>> board(height, vector<bool>(width, false));

    int query_num;
    cin >> query_num;

    char query_type;
    int r, c;
    int ra, ca, rb, cb;

    UnionFind union_find(width * height);

    for (int i = 0; i < query_num; ++i) {
        cin >> query_type;
        if (query_type == '1') {
            cin >> r >> c;
            r--; c--;
            run_query1(board, r, c, height, width, union_find);
        } else if (query_type == '2') {
            cin >> ra >> ca >> rb >> cb;
            ra--; ca--; rb--; cb--;
            run_query2(board, ra, ca, rb, cb, width, union_find);
        }
    }
    
    return 0;
}