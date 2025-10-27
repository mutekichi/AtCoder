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
    for (long long i = 0; i < v.size(); i++)
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

long long f(long long n, vector<long long> &f_lists)
{
    cout << "processing... " << n << endl;
    if (n == 0)
    {
        return 1;
    }
    if (n == 1)
    {
        return 2;
    }
    else if (n == 2)
    {
        return 3;
    }
    else
    {
        if (f_lists[n] == -1)
        {
            long long ans = f(n - 2ll, f_lists) * 2ll + f(n - 3ll, f_lists);
            f_lists[n] = ans;
            return ans;
        }
        else
        {
            return f_lists[n];
        }
    }
}

int main()
{

    long long n = 30ll;
    vector<long long> f_lists(n + 3ll, -1ll);

    cout << f(n, f_lists) << endl;

    return 0;
}
