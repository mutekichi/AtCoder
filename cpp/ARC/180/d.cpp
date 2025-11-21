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

class debug_cout {
public:
    debug_cout(bool debug) : debug(debug) {}

    template<typename T>
    debug_cout& operator<<(const T& value) {
        if (debug) {
            cout << value;
        }
        return *this;
    }

    debug_cout& operator<<(std::ostream& (*manip)(std::ostream&)) {
        if (debug) {
            manip(std::cout);
        }
        return *this;
    }

private:
    bool debug;
};


/**
 * @brief Segment Tree
 * 
 * @tparam T 
 * @param data vector of elements with type T
 * @param op an associative binary operation
 * @param identity an identity element for the operation
*/
template<typename T>
class SegmentTree {
public:
    SegmentTree(const vector<T>& data, function<T(T, T)> op, T identity)
        : op(op), identity(identity) {
        n = data.size();
        size = 1;
        while (size < n) size *= 2;
        tree.resize(2 * size, identity);
        build(data);
    }

    T query(int l, int r) {
        T result_left = identity, result_right = identity;
        l += size;
        r += size;
        while (l < r) {
            if (l & 1) result_left = op(result_left, tree[l++]);
            if (r & 1) result_right = op(tree[--r], result_right);
            l >>= 1;
            r >>= 1;
        }
        return op(result_left, result_right);
    }

    void update(int p, T value) {
        p += size;
        tree[p] = value;
        while (p > 1) {
            p >>= 1;
            tree[p] = op(tree[p * 2], tree[p * 2 + 1]);
        }
    }

private:
    int n;
    int size;
    vector<T> tree;
    function<T(T, T)> op;
    T identity;

    void build(const vector<T>& data) {
        
        for (int i = 0; i < n; ++i) {
            tree[size + i] = data[i];
        }
        
        for (int i = n; i < size; ++i) {
            tree[size + i] = identity;
        }
        
        for (int i = size - 1; i > 0; --i) {
            tree[i] = op(tree[i * 2], tree[i * 2 + 1]);
        }
    }
};


struct edge {
    int max;
    int index;
};

struct edge_min {
    int min;
    int min_index;
};
debug_cout dbgcout(true);

int main() {

    int n, q;
    cin >> n >> q;

    vector<edge> data(n);
    vector<edge_min> data_min(n);

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        data[i] = edge{a, i};
        data_min[i] = edge_min{a, i};
    }

    int INF = INT_MAX;

    SegmentTree<edge> st(
        data,
        [](edge a, edge b) {
            return edge{max(a.max, b.max), a.max > b.max ? a.index : b.index};
        },
        edge{0, 0}
    );

    SegmentTree<edge_min> st_min(
        data_min,
        [](edge_min a, edge_min b) {
            return edge_min{min(a.min, b.min), a.min < b.min ? a.min_index : b.min_index};
        },
        edge_min{INF, 0}
    );

    for (int i = 0; i < q; ++i) {
        int left, right;
        cin >> left >> right;

        edge max_value = st.query(left, right + 1);
        
        if (max_value.index == left) {
            edge_min min_value = st_min.query(left + 1, right + 1);
            edge second_max = st.query(min_value.min_index, right + 1);
            cout << max_value.max + min_value.min + second_max.max << endl;
        }

        else if (max_value.index == right) {
            edge_min min_value = st_min.query(left, right);
            edge second_max = st.query(left, min_value.min_index);
            cout << max_value.max + min_value.min + second_max.max << endl;
        }

        else {
            
        }

    }
    
    return 0;
}
