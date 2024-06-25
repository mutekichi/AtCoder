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

debug_cout dbgcout(true);

int main() {

    int n;
    cin >> n;

    vector<vector<int>> directed_graph(n);
    vector<vector<int>> reversed_directed_graph(n);

    vector<int> irijisuu(n, 0);


    vector<bool> is_seen(n, false);

    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        directed_graph[i].push_back(m - 1);
        reversed_directed_graph[m - 1].push_back(i);
        irijisuu[m - 1]++;
    }


    int start_node = -1;
    for (int i = 0; i < n; ++i) {
        if (irijisuu[i] > 1) {
            start_node = i;
        }
        break;
    }
    
    int nodes_loop = 0;
    int next_node = -1;

    while (true) {
        if (is_seen[next_node]) {
            nodes_loop = next_node;
            break;
        }
        is_seen[next_node] = true;
        next_node = directed_graph[next_node][0];
        ++nodes_loop;
    }

    vector<int> next_start_nodes;

    for (int i = 0; i < n; ++i) {
        if (irijisuu[i] > 1) {
            next_start_nodes.push_back(i);
        }
    }

    vector<int> counts(next_start_nodes.size(), 0);

    for (int i = 0; i < next_start_nodes.size(); ++i) {
        int count = 0;
        int next_node = next_start_nodes[i];
        while (reversed_directed_graph[next_node].size() == 1) {
            next_node = reversed_directed_graph[next_node][0];
            ++count;
        }
        counts[i] = count;
    }

    int sum = 0;

    sum += nodes_loop * (nodes_loop - 1) / 2;

    for (int i = 0; i < counts.size(); ++i) {
        sum += counts[i] * (counts[i] - 1) / 2;
        sum += nodes_loop * counts[i];
    }

    cout << sum << endl;

    return 0;
}