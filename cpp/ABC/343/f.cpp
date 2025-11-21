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

using num_and_count = pair<int, int>;
using num_and_count_pair = pair<num_and_count, num_and_count>;

num_and_count merge (num_and_count nc1, num_and_count nc2) {
    if (nc1.first == nc2.first) {
        return make_pair(nc1.first, nc1.second + nc2.second);
    } else if (nc1.first < nc2.first) {
        return nc2;
    } else return nc1;
}

num_and_count_pair operation(num_and_count_pair ncp1, num_and_count_pair ncp2) {
    if (ncp1.first.first == ncp2.first.first) {
        num_and_count new_nc2 = merge(ncp1.second, ncp2.second);
        return make_pair(merge(ncp1.first, ncp2.first), new_nc2);
    }
    else if (ncp1.first.first < ncp2.first.first) {
        num_and_count new_nc2 = merge(ncp1.first, ncp2.second);
        return make_pair(merge(ncp1.first, ncp2.first), new_nc2);
    }
    else {
        num_and_count new_nc2 = merge(ncp1.second, ncp2.first);
        return make_pair(merge(ncp1.first, ncp2.first), new_nc2);
    }

}

int main() {

    int n, q;

    cin >> n >> q;

    vector<num_and_count_pair> data(n);

    int a;

    for (int i = 0; i < n; ++i) {
        cin >> a;
        data[i] = make_pair(make_pair(a, 1), make_pair(0, 0));
    }

    num_and_count_pair identity = make_pair(make_pair(0, 0), make_pair(0, 0));

    SegmentTree<num_and_count_pair> st(
        data,
        operation,
        identity
    );

    char query_type;
    int target_index, target_value;
    int query_left, query_right;

    for (int i = 0; i < q; ++i) {
        cin >> query_type;
        if (query_type == '1') {
            cin >> target_index >> target_value;
            --target_index;
            st.update(target_index, make_pair(make_pair(target_value, 1), make_pair(0, 0)));
        } else {
            cin >> query_left >> query_right;
            --query_left;
            num_and_count_pair result = st.query(query_left, query_right);
            cout << result.second.second << endl;
        }
    }
    
    
    return 0;
}