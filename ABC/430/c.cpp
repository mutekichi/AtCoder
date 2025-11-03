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
    int n, a, b;
    cin >> n >> a >> b;
    string s;
    cin >> s;

    int ans = 0;
    int cur_l = 0;
    int cur_r = 0;

    int a_count = 0;
    int b_count = 0;
    int to_add = 1;

    while (cur_r < n)
    {
        // cout << "cur_l: " << cur_l << " cur_r " << cur_r << " ac " << a_count << " bc " << b_count << " ans " << ans << endl;
        if (a_count <= a)
        {
            if (s[cur_r] == 'a')
            {
                ++a_count;
            }
            else
            {
                ++b_count;
            }

            cur_r++;
        }
        else
        {
            if (b_count >= b)
            {
                to_add = 1;
                cur_l++;
                if (s[cur_l - 1] == 'a')
                {
                    --a_count;
                }
                else
                {
                    --b_count;
                }
            }
            else
            {
                ans += to_add;
                cur_r++;
                if (s[cur_r] == 'a')
                {
                    ++a_count;
                }
                else
                {
                    ++b_count;
                }
                to_add++;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
