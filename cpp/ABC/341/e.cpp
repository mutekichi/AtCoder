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
 * @brief Lazy Propagation Segment Tree 
 * 
 * @tparam T element type of the segment tree
 * @tparam U element type of the lazy propagation operation
 * @param data vector of elements with type T
 * @param operation an associative binary operation
 * @param identity_operation an identity element for the operation
 * @param mapping a mapping function
 * @param composition a composition function
 * @param identity_mapping an identity element for the mapping
 * 
 * @example
 * 
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
 */
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

    // set value x at position p
    void set(int p, T x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        tree[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    // get value at position p
    T get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return tree[p];
    }

    // get operation result in range [l, r)
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

    // apply function f to all elements in range [l, r)
    T all_prod() { return tree[1]; }

    // apply function f to element at position p
    void apply(int p, U f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        tree[p] = mapping(tree[p], f);
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    // apply function f to all elements in range [l, r)
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

debug_cout dbgcout(true);

struct element {
    bool is_all_0;
    bool is_all_1;
    bool is_identity;
};

element flip_element(element a) {
    return element{a.is_all_1, a.is_all_0, a.is_identity};
};

string to_string(element a) {
    if (a.is_all_0) {
        return "0";
    } else if (a.is_all_1) {
        return "1";
    } else return "?";
}

int main() {

    int n, q;
    cin >> n >> q;

    vector<element> data;

    string s;
    cin >> s;

    bool reverse = false;

    for (int i = 0; i < n; ++i) {
        if (s[i] == '0' ^ reverse) {
            data.push_back({true, false, false});
        } else {
            data.push_back({false, true, false});
        }
        
        reverse = !reverse;
    }
    
    LazyPropagationSegmentTree<element, bool> st(
        data,
        [](element a, element b) { 
            if (a.is_identity) return b;
            else if (b.is_identity) return a;
            else return element{a.is_all_0 && b.is_all_0, a.is_all_1 && b.is_all_1, false};
        },
        element{true, true, true},
        [](element a, bool b) { return b ? flip_element(a) : a;},
        [](bool a, bool b) { return a ^ b;},
        false
    );

    // element dbgelement = [](element a, element b) { 
    //     if (a.is_identity) return b;
    //     else if (b.is_identity) return a;
    //     else return element{a.is_all_0 && b.is_all_0, a.is_all_1 && b.is_all_1, false};
    // }(data[0], element{true, true, true});

    // cout << to_string(dbgelement) << endl;
    // return 0;

    // cout << to_string(st.get(0)) << endl; return 0;

    for (int i = 0; i < q; ++i) {
        int qtype, l, r;
        cin >> qtype >> l >> r;

        if (qtype == 1) {
            st.apply(l - 1, r, true);
        } else {
            element result = st.prod(l - 1, r);
            if (result.is_all_0 || result.is_all_1) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
    
    return 0;
}
