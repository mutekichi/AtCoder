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

debug_cout dbgcout(true);

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
 * @link https://betrue12.hateblo.jp/entry/2020/09/23/005940
 * 
 * @example
 * 
    int identity_operation = 0;
    int identity_mapping = -1;
    
    LazyPropagationSegmentTree<S, F> st(
        // data
        heights,
        // operation
        [](S a, S b) { return max(a, b); },
        // identity_operation
        identity_operation,
        // mapping
        [](S a, F b) { return b == -1 ? a : b;},
        // composition
        [](F a, F b) { return b == -1 ? a : b;},
        // identity_mapping
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


template<typename T>
void print_vector(vector<T> v, bool debug) {
    for (int i = 0; i < v.size(); i++) {
        if (debug) {
            dbgcout << v[i] << " ";
        }
        else {
            cout << v[i] << " ";
        }
    }
    if (debug) {
        dbgcout << endl;
    }
    else {
        cout << endl;
    }
}

double DOUBLE_MAX = 1e12;

double calc(pair<long long, long long> a) {
    if (a.second == 1ll) return DOUBLE_MAX;
    else {
        return (double)a.first / (double)(a.second - 1ll);
    }
}

int main() {

    int n;
    cin >> n;

    vector<long long> a(n);
    vector<long long> b(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    vector<double> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = calc(make_pair(a[i], b[i]));
    }

    SegmentTree<long long> st_mul(
        b,
        [](long long a, long long b) { return a * b; },
        1ll
    );

    SegmentTree<double> st_min(
        c,
        [](double a, double b) { return min(a, b); },
        DOUBLE_MAX
    );
    
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 3) {
            int l, r;
            cin >> l >> r;
            long long init = a[l - 1];
            while(l < r && init > st_min.query(l, r)) {
                if (init < calc(make_pair(a[l], b[l]))) {
                    init += a[l];
                    l++;
                } else {
                    init *= b[l];
                    l++;
                }
            }
            if (l == r) cout << init << endl;
            else cout << init * st_mul.query(l, r) << endl;
        }
        else {
            int i;
            cin >> i;
            i--;
            long long x;
            cin >> x;
            if (type == 1) {
                a[i] = x;
                st_min.update(i, calc(make_pair(a[i], b[i])));
                // dbgcout << "a[i]: " << a[i] << endl
            } else if (type == 2) {
                b[i] = x;
                st_mul.update(i, b[i]);
                st_min.update(i, calc(make_pair(a[i], b[i])));
                // dbgcout << "b[i]: " << b[i] << endl;
            }
        }
    }


    return 0;
}
