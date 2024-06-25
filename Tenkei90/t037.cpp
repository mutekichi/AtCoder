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


int main() {

    int w, n;
    cin >> w >> n;

    vector<tuple<int, int, long long>> dishes(n);

    for (int i = 0; i < n; ++i) {
        int minimum, maximum;
        long long value;
        cin >> minimum >> maximum >> value;
        dishes[i] = make_tuple(minimum, maximum, value);
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(w + 1, -(LONG_MAX - 1)));

    dp[0][0] = 0;
    for (int i = 1; i < w + 1; ++i) {
        dp[0][i] = -LONG_MAX;
    }
    for (int i = 1; i <= n; ++i) {
        vector<long long> prev(w + 1);
        for (int j = 0; j <= w; ++j) {
            prev[j] = dp[i - 1][j];
        }
        SegmentTree<long long> segtree(prev, [](long long num1, long long num2) {
            return max(num1, num2);
        }, -(LONG_MAX - 1));
        int minimum = get<0>(dishes[i - 1]);
        int maximum = get<1>(dishes[i - 1]);
        long long value = get<2>(dishes[i - 1]);
        for (int j = 0; j <= w; ++j) {
            if (j < minimum) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(dp[i - 1][j], segtree.query(max(0, j - maximum), j - minimum + 1) + value);
            }
        }
    }

    if (dp[n][w] < 0) cout << -1 << endl;
    else cout << dp[n][w] << endl;
    
    return 0;
}