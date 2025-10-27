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

void print_set(set<int> &s)
{
    cout << "contains: ";
    for (const auto elem : s)
    {
        cout << elem << " ";
    }
    cout << endl;
}

int main()
{

    int t;
    cin >> t;

    for (int ti = 0; ti < t; ++ti)
    {
        int n, m, k;
        cin >> n >> m >> k;
        string str;
        cin >> str;

        vector<int> b_indices;
        for (int i = 0; i < n; ++i)
        {
            if (str[i] == 'B')
            {
                b_indices.push_back(i);
            }
        }

        vector<vector<int>> to_nodes(n);

        for (int mi = 0; mi < m; ++mi)
        {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            to_nodes[v].push_back(u);
        }

        set<int> s;
        for (const auto b_index : b_indices)
        {
            for (const auto to_node : to_nodes[b_index])

            {
                s.insert(to_node);
            }
        }

        for (int i = 0; i < 2 * k - 1; ++i)
        {
            // print_set(s);
            set<int> subset;
            for (int j = 0; j < n; ++j)
            {
                if (s.find(j) == s.end())
                {
                    subset.insert(j);
                }
            }
            s.clear();
            for (const auto node : subset)
            {
                for (const auto to_node : to_nodes[node])
                {
                    s.insert(to_node);
                }
            }
        }
        if (s.find(0) == s.end())
        {
            cout << "Bob" << endl;
        }
        else
        {
            cout << "Alice" << endl;
        }
    }
    return 0;
}
