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

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> heads(n);
    vector<int> bodies(m);
    for (int i = 0; i < n; ++i)
    {
        cin >> heads[i];
    }
    for (int i = 0; i < m; ++i)
    {
        cin >> bodies[i];
    }

    sort(heads.begin(), heads.end(), greater<int>());
    sort(bodies.begin(), bodies.end(), greater<int>());

    // output_vector(heads, false);
    // output_vector(bodies, false);

    int h_idx = 0;

    int counts = 0;

    for (int i = 0; i < m; ++i)
    {
        if (h_idx == n - 1)
        {
            if (heads[h_idx] <= bodies[i])
            {
                counts++;
            }

            if (counts >= k)
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
            return 0;
        }

        int body = bodies[i];
        while (heads[h_idx] > body)
        {
            h_idx++;
            if (h_idx == n - 1)
            {
                if (heads[h_idx] <= body)
                {
                    counts++;
                }

                if (counts >= k)
                {
                    cout << "Yes" << endl;
                }
                else
                {
                    cout << "No" << endl;
                }
                return 0;
            }
        }

        counts++;
        h_idx++;
    }

    if (counts >= k)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }

    return 0;
}
