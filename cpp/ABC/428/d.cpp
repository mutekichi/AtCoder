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

long long count_heiho(
    long long a)
{
    if (a < 1)
    {
        return 0;
    }

    long long low = 1ll;
    long long high = 10000000000LL;

    long long ans = 0;

    while (low <= high)
    {
        long long mid = low + (high - low) / 2ll;
        if (mid * mid <= a)
        {
            ans = mid;
            low = mid + 1ll;
        }
        else
        {
            high = mid - 1ll;
        }
    }

    return ans;
}

long long count_heiho_range(
    long long a,
    long long b)
{
    long long cb = count_heiho(b);
    long long ca = count_heiho(a - 1);
    return cb - ca;
}

long long _judge(long long c, long long d)
{
    long long keta = 1;
    long long ans = 0;
    while (true)
    {
        if (d < keta * 10ll)
        {
            break;
        }
        long long heihos = count_heiho_range(c * keta * 10ll + keta, (c + 1ll) * keta * 10ll - 1ll);
        ans += heihos;
        keta *= 10ll;
    }
    long long heihos = count_heiho_range(c * keta * 10ll + keta, c * keta * 10ll + d);

    ans += heihos;
    return ans;
}

void judge()
{
    long long c, d;
    cin >> c >> d;
    cout << _judge(c, c + d) - _judge(c, c - 1) << endl;
}

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i)
    {
        judge();
    }

    return 0;
}
