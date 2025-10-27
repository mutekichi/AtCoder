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

void judge(
    int factor,
    int last_invalid)
{
    if (factor == 0 && last_invalid == -1)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
    return;
    // cout << "factor: " << factor << " lv: " << last_invalid << " size: " << kakkos.size() << endl;
}

int main()
{
    int q;
    cin >> q;
    stack<bool> kakkos; // True: (
    int factor = 0;
    int last_invalid = -1;

    for (int i = 0; i < q; ++i)
    {
        int qtype;
        cin >> qtype;
        if (qtype == 1)
        {
            char kakko;
            cin >> kakko;
            if (kakko == '(')
            {
                factor += 1;
                kakkos.push(true);
                judge(factor, last_invalid);
            }
            else
            {
                factor -= 1;
                kakkos.push(false);
                if (factor < 0 && last_invalid == -1)
                {
                    last_invalid = kakkos.size();
                }
                judge(factor, last_invalid);
            }
        }
        else
        {
            bool top = kakkos.top();
            kakkos.pop();
            if (top)
                factor -= 1;
            else
                factor += 1;
            if (int(kakkos.size()) == last_invalid - 1)
            {
                last_invalid = -1;
            }
            judge(factor, last_invalid);
        }
    }

    return 0;
}
