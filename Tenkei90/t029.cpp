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
#include <assert.h>

using namespace std;

template<typename T, typename U>
class LazyPropagationSegmentTree {
public:
    LazyPropagationSegmentTree(
        const vector<T>& data,
        function<T(T, T)> operation,
        T identity_operation,
        function<T(T, U)> mapping,
        function<U(U, U)> composition,
        U identity_mapping
    ) : _n(data.size()), 
        operation(operation), 
        identity_operation(identity_operation), 
        mapping(mapping), 
        composition(composition), 
        identity_mapping(identity_mapping) {
        
        log = ceil_pow2(_n);
        size = 1 << log;
        tree = vector<T>(2 * size, identity_operation);
        lazy = vector<U>(size, identity_mapping);
        for (int i = 0; i < _n; i++) {
            tree[size + i] = data[i];
        }
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, T x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        tree[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    T get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return tree[p];
    }

    T prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return identity_operation;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push(r >> i);
        }

        T sml = identity_operation, smr = identity_operation;
        while (l < r) {
            if (l & 1) sml = operation(sml, tree[l++]);
            if (r & 1) smr = operation(tree[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return operation(sml, smr);
    }

    T all_prod() { return tree[1]; }

    void apply(int p, U f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        tree[p] = mapping(tree[p], f);
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    void apply(int l, int r, U f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

private:
    int _n, size, log;
    vector<T> tree;
    vector<U> lazy;
    function<T(T, T)> operation;
    T identity_operation;
    function<T(T, U)> mapping;
    function<U(U, U)> composition;
    U identity_mapping;

    void update(int k) {
        tree[k] = operation(tree[2 * k], tree[2 * k + 1]);
    }

    void all_apply(int k, U f) {
        tree[k] = mapping(tree[k], f);
        if (k < size) lazy[k] = composition(lazy[k], f);
    }

    void push(int k) {
        all_apply(2 * k, lazy[k]);
        all_apply(2 * k + 1, lazy[k]);
        lazy[k] = identity_mapping;
    }

    int ceil_pow2(int n) {
        int x = 0;
        while ((1U << x) < (unsigned int)(n)) x++;
        return x;
    }
};

void solve_O_wn(int w, int n) {
    vector<int> heights(w, 0);
    int left, right;

    for (int i_block = 0; i_block < n; ++i_block) {
        cin >> left >> right;
        left--; right--;
        int max_height= 0;
        for (int i_width = left; i_width <= right; ++i_width) {
            max_height = max(max_height, heights[i_width]);
        }
        for (int i_width = left; i_width <= right; ++i_width) {
            heights[i_width] = max_height + 1;
        }
    }
}



void solve_O_nlogw(int w, int n) {

    vector<int> heights(w, 0);

    using S = int;
    using F = int;
    
    
    int identity_operation = 0;
    int identity_mapping = -1;
    
    LazyPropagationSegmentTree<S, F> st(
        heights,
        [](S a, S b) { return max(a, b); },
        identity_operation,
        [](S a, F b) { return b == -1 ? a : b;},
        [](F a, F b) { return b == -1 ? a : b;},
        identity_mapping
    );

    for (int i_block = 0; i_block < n; ++i_block) {
        int left, right;
        cin >> left >> right;
        left--; right--;
        int max_height = st.prod(left, right + 1);
        cout << max_height + 1 << endl;
        st.apply(left, right + 1, max_height + 1);
    }
}

int main() {

    int w, n;
    cin >> w >> n;

    // if (n <= 9000) {
    //     if (w <= 9000) {
    //         solve_O_wn(w, n);
    //     }
    // } else {
    //     solve_O_nlogw(w, n);
    // }
    
    solve_O_nlogw(w, n);

    return 0;
}