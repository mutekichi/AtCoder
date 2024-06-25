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

debug_cout dbgcout(false);

// ナップサックdp
// neibors.first: score,
// neibors.second: weight,
// value: max_weight

long long calc_score(vector<pair<long long, long long>> &neighbors, long long value) {
    long long n = neighbors.size();
    if (n == 0) return 1ll;
    vector<vector<long long>> dp(n + 1, vector<long long>(value + 1, 0));
    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j <= value; ++j) {
            if (j >= neighbors[i].second) {
                dp[i + 1][j] = max(dp[i][j], dp[i][j - neighbors[i].second] + neighbors[i].first);
            } else {
                dp[i + 1][j] = dp[i][j];
            }
        }
    }
    return dp[n][value] + 1ll;
}
int main() {

    long long n, m;
    cin >> n >> m;
    vector<vector<long long>> graph(n);

    for (long long i = 0; i < m; ++i) {
        long long a, b;
        cin >> a >> b;
        --a;
        --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<long long> values(n);
    vector<pair<long long, long long>> edges_to_calc_score;
    for (long long i = 0; i < n; ++i) {
        cin >> values[i];
        edges_to_calc_score.push_back({values[i], i});
    }

    sort(edges_to_calc_score.begin(), edges_to_calc_score.end());

    vector<long long> scores(n, -1);

    for (long long i = 0; i < n; ++i) {
        long long node = edges_to_calc_score[i].second;
        long long value = edges_to_calc_score[i].first;
        dbgcout << "node: " << node << " value: " << value << endl;
        long long score = 0ll;
        vector<pair<long long, long long>> neighbors;
        for (auto neighbor : graph[node]) {
            if (scores[neighbor] != -1) {
                neighbors.push_back(make_pair(scores[neighbor], values[neighbor]));
                dbgcout << "neighbor: " << neighbor << " score: " << scores[neighbor] << " value: " << values[neighbor] << endl;
            }
        }
        
        score = calc_score(neighbors, value - 1);

        dbgcout << score << endl;
        dbgcout << endl;
        scores[node] = score;
    }

    for (long long i = 0; i < n; ++i) {
        dbgcout << "node: " << i << " score: " << scores[i] << endl;
    }

    long long ans = 0;

    for (long long i = 0; i < n; ++i) {
        long long init_num;
        cin >> init_num;
        ans += init_num * scores[i];
    }
    
    cout << ans << endl;

    return 0;
}
