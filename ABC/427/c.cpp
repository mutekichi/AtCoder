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

private:
    bool debug;
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

int edges_to_cut_to_get_bipartite_graph(
    vector<pair<int, int>> &edges,
    int color)
{
    int sum = 0;
    for (const auto edge : edges)
    {
        int u = edge.first;
        int v = edge.second;
        if (!(((color >> u) & 1) ^ (color >> v) & 1))
        {
            sum++;
        }
    }
    return sum;
}

int main()
{

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    vector<pair<int, int>> edges(m);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);

        edges[i] = make_pair(u, v);
    }

    int ans = 1000000;
    for (int i = 0; i < (1 << n); ++i)
    {
        ans = min(ans, edges_to_cut_to_get_bipartite_graph(edges, i));
    }

    cout << ans << endl;

    return 0;
}
