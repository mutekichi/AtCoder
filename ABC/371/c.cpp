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
void output_vector(vector<T> v, bool debug) {
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

int main() {

    int n;
    cin >> n;

    int mg;
    int mh;

    cin >> mg;
    cout << mg << endl;

    vector<vector<int>> g(n);
    vector<vector<int>> h(n);

    for (int i = 0; i < mg; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        
        g[a].push_back(b);
        g[b].push_back(a);
    }

    cin >> mh;
    cout << mh << endl;

    for (int i = 0; i < mh; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        
        h[a].push_back(b);
        h[b].push_back(a);
    }

    vector<vector<long long>> score(n, vector<long long>(n, 0));

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < i; ++j) {
            long long s;
            cin >> s;
            score[i][j] = s;
            score[j][i] = s;
        }
    }

    for (int i = 0; i < n; ++i) {
        output_vector(score[i], true);
    }

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);

    long long ans_min = LLONG_MAX;

    do {
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < j; ++k) {
                    bool exists_in_h = find(g[perm[j]].begin(), g[perm[j]].end(), perm[k]) != g[perm[j]].end();
                    bool exists_in_g = find(h[i].begin(), h[i].end(), perm[k]) != h[i].end();
                    if (exists_in_g == exists_in_h) {
                        ans += score[j + 1][k + 1];
                    }
                }
            }
        }
        ans_min = min(ans_min, ans);
    } while (next_permutation(perm.begin(), perm.end()));

    cout << ans_min << endl;

    return 0;
}
