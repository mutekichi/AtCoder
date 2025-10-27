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

int main()
{

    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    map<string, int> str_counts;

    for (int i = 0; i < n - k + 1; ++i)
    {
        string trimmed = s.substr(i, k);
        str_counts[trimmed]++;
    }

    int max_counts = 0;
    for (const auto &[key, value] : str_counts)
    {
        if (value > max_counts)
        {
            max_counts = value;
        }
    }

    cout << max_counts << endl;
    bool is_first = true;
    for (const auto &[key, value] : str_counts)
    {
        if (value == max_counts)
        {
            if (!is_first)
            {
                cout << " ";
            }
            else
            {
                is_first = false;
            }
            cout << key;
        }
    }
    cout << endl;

    return 0;
}
