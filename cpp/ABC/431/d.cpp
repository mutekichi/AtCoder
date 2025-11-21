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
    int n;
    cin >> n;
    vector<long long> weights(n);
    vector<long long> hs(n);
    vector<long long> bs(n);

    long long wsum = 0;

    for (int i = 0; i < n; ++i)
    {
        cin >> weights[i] >> hs[i] >> bs[i];
        wsum += weights[i];
    }

    const long long center = wsum + 10ll;
    // cout << "center " << center << endl;

    // vector<vector<long long>> dp(n + 1, vector<long long>(center * 2ll, -1));

    vector<long long> dp_bef(center * 2ll, -1);
    vector<long long> dp_aft(center * 2ll, -1);

    dp_bef[center] = 0;

    for (int i = 0; i < n; ++i)
    {
        long long w = weights[i];
        long long h = hs[i];
        long long b = bs[i];

        // head case
        for (long long j = w; j < center * 2ll; ++j)
        {
            if (dp_bef[j] == -1)
                continue;
            dp_aft[j - w] = max(dp_aft[j - w], dp_bef[j] + h);
            // cout << "dp at " << i + 1 << " " << j - w << " " << dp[i + 1][j - w] << endl;
        }
        // body case
        for (long long j = 0; j < center * 2ll - w; ++j)
        {
            if (dp_bef[j] == -1)
                continue;
            dp_aft[j + w] = max(dp_aft[j + w], dp_bef[j] + b);
        }
        for (long long j = 0; j < center * 2ll; ++j)
        {
            dp_bef[j] = dp_aft[j];
        }
    }

    long long ans = -1;
    for (long long j = center; j < center * 2ll; ++j)
    {
        ans = max(ans, dp_aft[j]);
    }
    cout << ans << endl;

    return 0;
}
