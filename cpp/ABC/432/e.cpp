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

    void incr()
    {
        if (debug)
        {
            debug_loop_counter++;
            if (debug_loop_counter >= MAX_DEBUG_LOOPS)
            {
                std::cout << "Debug exit: Loop limit (" << MAX_DEBUG_LOOPS << ") reached." << std::endl;
                exit(0);
            }
        }
    }

private:
    bool debug;
    long long debug_loop_counter = 0;
    const long long MAX_DEBUG_LOOPS = 10;
};

debug_cout dbgcout(true);

template <typename T>
void output_vector(vector<T> v, bool debug)
{
    for (long long i = 0; i < v.size(); i++)
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

/**
 * @brief Segment Tree
 *
 * @tparam T
 * @param data vector of elements with type T
 * @param op an associative binary operation
 * @param identity an identity element for the operation
 */
template <typename T>
class SegmentTree
{
public:
    SegmentTree(const vector<T> &data, function<T(T, T)> op, T identity)
        : op(op), identity(identity)
    {
        n = data.size();
        size = 1;
        while (size < n)
            size *= 2;
        tree.resize(2 * size, identity);
        build(data);
    }

    T query(long long l, long long r)
    {
        T result_left = identity, result_right = identity;
        l += size;
        r += size;
        while (l < r)
        {
            if (l & 1)
                result_left = op(result_left, tree[l++]);
            if (r & 1)
                result_right = op(tree[--r], result_right);
            l >>= 1;
            r >>= 1;
        }
        return op(result_left, result_right);
    }

    void update(long long p, T value)
    {
        p += size;
        tree[p] = value;
        while (p > 1)
        {
            p >>= 1;
            tree[p] = op(tree[p * 2], tree[p * 2 + 1]);
        }
    }

private:
    long long n;
    long long size;
    vector<T> tree;
    function<T(T, T)> op;
    T identity;

    void build(const vector<T> &data)
    {

        for (long long i = 0; i < n; ++i)
        {
            tree[size + i] = data[i];
        }

        for (long long i = n; i < size; ++i)
        {
            tree[size + i] = identity;
        }

        for (long long i = size - 1; i > 0; --i)
        {
            tree[i] = op(tree[i * 2], tree[i * 2 + 1]);
        }
    }
};

int main()
{

    long long n, q;
    cin >> n >> q;
    vector<long long> a(n);

    long long sum = 0;

    for (long long i = 0; i < n; ++i)
    {
        cin >> a[i];
        sum += a[i];
    }

    long long M = 500005ll;
    vector<long long> counts(M, 0);
    vector<long long> sums(M, 0);
    for (long long i = 0; i < n; ++i)
    {
        counts[a[i]]++;
        sums[a[i]] += a[i];
    }

    SegmentTree<long long> st_count(
        counts,
        [](long long a, long long b)
        { return a + b; }, 0);

    SegmentTree<long long> st_sums(
        sums,
        [](long long a, long long b)
        { return a + b; }, 0);

    for (long long nq = 0; nq < q; ++nq)
    {
        long long tq, l, r;
        cin >> tq >> l >> r;
        if (tq == 1ll)
        {

            st_count.update(a[l - 1ll], st_count.query(a[l - 1ll], a[l - 1ll] + 1ll) - 1ll);
            st_count.update(r, st_count.query(r, r + 1ll) + 1ll);

            st_sums.update(a[l - 1ll], st_sums.query(a[l - 1ll], a[l - 1ll] + 1ll) - a[l - 1ll]);
            st_sums.update(r, st_sums.query(r, r + 1ll) + r);

            a[l - 1ll] = r;
        }
        else
        {
            if (l > r)
            {
                cout << l * n << endl;
                continue;
            }

            long long n_lower = st_count.query(0, l);
            long long n_upper = st_count.query(r, M);
            long long sum_lower = st_sums.query(l, r);

            cout << l * n_lower + r * n_upper + sum_lower << endl;
        }
    }

    return 0;
}
