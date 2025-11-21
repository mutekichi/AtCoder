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

long long gcd(long long a, long long b)
{
    if (a % b == 0)
    {
        return b;
    }
    else
    {
        return gcd(b, a % b);
    }
}

int main()
{
    long long n, x, y;
    cin >> n >> x >> y;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    long long g = gcd(x, y);

    long long nx = x / g;
    long long ny = y / g;

    long long div = ny - nx;

    sort(a.begin(), a.end());

    long long ans = 0;

    long long ref = a[0];
    ans += ref;

    for (int i = 1; i < n; ++i)
    {
        if ((a[i] - ref) % div != 0)
        {
            cout << -1 << endl;
            return 0;
        }

        long long to_add = ref - (a[i] - ref) / div * nx;
        if (to_add < 0)
        {
            cout << -1 << endl;
            return 0;
        }
        ans += to_add;
    }
    cout << ans << endl;
    return 0;
}
