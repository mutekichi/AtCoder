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

void print_vector(vector<int> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;
}


int main() {

    int n;
    cin >> n;

    vector<pair<long long, long long>> ranges(n);
    vector<long long> existing_x;

    for (int i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        ranges[i] = make_pair(x, y);
        existing_x.push_back(x);
        existing_x.push_back(y);
    }

    sort(existing_x.begin(), existing_x.end());
    existing_x.erase(unique(existing_x.begin(), existing_x.end()), existing_x.end());

    vector<pair<int, int>> compressed_ranges(n);
    
    for (int i = 0; i < n; ++i) {
        long long x = ranges[i].first;
        long long y = ranges[i].second;
        int x_index = lower_bound(existing_x.begin(), existing_x.end(), x) - existing_x.begin();
        int y_index = lower_bound(existing_x.begin(), existing_x.end(), y) - existing_x.begin();
        
        compressed_ranges[i] = make_pair(x_index * 2, y_index * 2);
    }

    vector<int> firsts;
    vector<int> seconds;

    for (int i = 0; i < n; ++i) {
        firsts.push_back(compressed_ranges[i].first);
        seconds.push_back(compressed_ranges[i].second);
    }
    
    sort(firsts.begin(), firsts.end());
    sort(seconds.begin(), seconds.end());

    print_vector(firsts);
    print_vector(seconds);
    
    int point_max = max(firsts[firsts.size() - 1], seconds[seconds.size() - 1]);

    vector<int> data(point_max + 1, 0);

   return 0;
}
