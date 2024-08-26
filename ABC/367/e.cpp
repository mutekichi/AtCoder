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

template<typename T>
void print_vector(vector<T> v) {
    for (long long i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

debug_cout dbgcout(false);

class UnionFind {
public:
    vector<long long> parent;
    vector<long long> rank;
    vector<long long> size;

    UnionFind(long long n) {
        parent.resize(n);
        rank.resize(n);
        size.resize(n);
        for (long long i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
            size[i] = 1;
        }
    }

    long long find(long long x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(long long x, long long y) {
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

    bool same(long long x, long long y) {
        return find(x) == find(y);
    }

    long long get_size(long long x) {
        return size[find(x)];
    }
};

long long pow(long long a, long long b) {
    long long res = 1;
    for (long long i = 0; i < b; i++) {
        res *= a;
    }
    return res;
}

long long __gcd(long long a, long long b) {
    if (b == 0) return a;
    return __gcd(b, a % b);
}

int main() {
    long long n, k;
    cin >> n >> k;

    vector<long long> x(n);
    vector<long long> a(n);
    vector<long long> usedx;
    for (long long i = 0; i < n; i++) {
        long long xi;
        cin >> xi;
        xi--;
        x[i] = xi;
        usedx.push_back(xi);
    }
    for (long long i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (k == 0) print_vector(a);
    else {
        // print_vector(x);
        // print_vector(usedx);
        sort(usedx.begin(), usedx.end());
        usedx.erase(unique(usedx.begin(), usedx.end()), usedx.end());

        long long m = usedx.size();

        dbgcout << "m: " << m << endl;
        // print_vector(usedx);
        vector<long long> b(m);
        vector<long long> y(m);

        for (long long i = 0; i < m; ++i) {
            b[i] = a[usedx[i]];
            //y[i] = x[usedx[i]];
            y[i] = lower_bound(usedx.begin(), usedx.end(), x[usedx[i]]) - usedx.begin();
        }

        vector<long long> loop_sizes(m, 0);
        vector<vector<long long>> loops(m);

        set<long long> loop_sizes_set;
        dbgcout << "here";

        for (long long i = 0; i < m; ++i) {
            if (loop_sizes[i] == 0) {
                long long current = i;
                long long loop_size = 0;
                while (loop_sizes[current] == 0) {
                    loops[i].push_back(current);
                    loop_sizes[current] = -1;
                    current = y[current];
                    loop_size++;
                }
                if (loop_sizes[current] == -1) {
                    loop_size -= loop_sizes[current];
                }
                loop_sizes_set.insert(loop_size);
                for (long long j : loops[i]) {
                    loop_sizes[j] = loop_size;
                }
            }
        }
        
        long long lcm_loop_sizes = 1ll;
        
        for (long long loop_size : loop_sizes_set) {
            lcm_loop_sizes = lcm_loop_sizes / __gcd(lcm_loop_sizes, loop_size) * loop_size;
        }

        long long res = k % lcm_loop_sizes;
        vector<long long> ans(n);

        dbgcout << "lcm_loop_sizes: " << lcm_loop_sizes << endl;
        dbgcout << "res: " << res << endl;

        for (long long i = 0; i < m; ++i) {
            long long index_at_loop = res % loop_sizes[i];
            long long current = i;
            for (long long j = 0; j < index_at_loop; ++j) {
                current = y[current];
            }
            long long current_index = i;
            for (long long j = 0; j < loop_sizes[i]; ++j) {
                ans[usedx[current_index]] = b[current];
                current = y[current];
                current_index = y[current_index];
            }
        }
    
        print_vector(ans);
    }

    return 0;
}