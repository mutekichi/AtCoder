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
    int debug_loop_counter = 0;
    const int MAX_DEBUG_LOOPS = 10;
};

debug_cout dbgcout(true);

template <typename T>
void output_vector(vector<T> v, bool debug)
{
    for (int i = 0; i < v.size(); i++)
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

bool is_safety(
    string &s, int node)
{
    if (s[node] == 'S')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    string s;
    cin >> s;

    // shorts[i_node][0 or 1] = [node_from, dist]
    vector<vector<pair<int, int>>> shorts(n, vector<pair<int, int>>(2, {-1, INT_MAX}));

    queue<tuple<int, int, int>> q; // current_node, dist, node_from

    for (int i = 0; i < n; ++i)
    {
        if (is_safety(s, i))
        {
            q.emplace(i, 0, i);
        }
    }

    while (!q.empty())
    {
        auto front = q.front();
        int current_node = get<0>(front);
        int current_dist = get<1>(front);
        int node_from = get<2>(front);
        q.pop();

        // cout << "current_node: " << current_node << " dist: " << current_dist << " from: " << node_from << endl;
        // dbgcout.incr();

        // 埋まっていたらパス
        if (shorts[current_node][0].second != INT_MAX && shorts[current_node][1].second != INT_MAX)
        {
            continue;
        }

        // 一つのみ訪問済み
        if (shorts[current_node][0].second != INT_MAX)
        {
            // 一つ目が自分自身ならパス
            if (shorts[current_node][0].first == node_from)
            {
                continue;
            }

            shorts[current_node][1] = {node_from, current_dist};

            for (const int next_node : graph[current_node])
            {
                q.emplace(next_node, current_dist + 1, node_from);
            }
        }
        else // 完全に未訪問
        {
            shorts[current_node][0] = {node_from, current_dist};
            for (const int next_node : graph[current_node])
            {
                q.emplace(next_node, current_dist + 1, node_from);
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        if (!is_safety(s, i))
        {
            cout << shorts[i][0].second + shorts[i][1].second << endl;
        }
    }

    return 0;
}
