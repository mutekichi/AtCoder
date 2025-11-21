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

long long find_min_index(
    vector<long long> &vec,
    long long t)
{
    auto it = lower_bound(vec.begin(), vec.end(), t);
    return (long long)(distance(vec.begin(), it));
}

int main()
{
    long long n, m, c;
    cin >> n >> m >> c;

    vector<long long> people(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> people[i];
    }

    sort(people.begin(), people.end());

    vector<pair<long long, long long>> _counts;

    long long prev = -1;
    long long count = 0;
    for (int i = 0; i < n; ++i)
    {
        long long prev_x = people[i];
        if (prev == -1 || prev == prev_x)
        {
            prev = prev_x;
            count += 1;
        }
        else
        {
            _counts.push_back(make_pair(count, prev));
            prev = prev_x;
            count = 1;
        }
    }
    _counts.push_back(make_pair(count, prev));

    // for (const auto c : counts)
    // {
    //     cout << c.first << " " << c.second << endl;
    // }

    long long counts_len = (long long)(_counts.size());

    vector<long long> people_counts(counts_len * 2ll);
    vector<long long> positions(counts_len * 2ll);

    for (long long i = 0; i < counts_len; ++i)
    {
        people_counts[i] = _counts[i].first;
        positions[i] = _counts[i].second;
    }

    long long farthest = positions[counts_len - 1];
    long long padding = m - 1ll - farthest;
    for (long long i = 0; i < counts_len; ++i)
    {
        positions[i] += padding;
    }

    for (long long i = 0; i < counts_len; ++i)
    {
        positions[counts_len + i] = positions[i] + m;
        people_counts[counts_len + i] = people_counts[i];
    }
    for (long long i = 1; i < counts_len * 2ll; ++i)
    {
        people_counts[i] += people_counts[i - 1ll];
    }

    // output_vector(positions, false);
    // output_vector(people_counts, false);

    long long ans = 0;

    for (long long i = 0; i < counts_len; ++i)
    {
        long long idx;
        long long prev_people = i == 0 ? 0 : people_counts[i - 1];
        idx = find_min_index(people_counts, c + prev_people);

        long long prev_pos = i == 0 ? 0 : positions[i - 1];
        long long cur_pos = positions[i];
        long long targ_pos = positions[idx];

        long long to_add = cur_pos - prev_pos;
        if (i == 0)
            to_add++;

        long long to_mul = (people_counts[idx] - prev_people);
        // cout << people_counts[idx] << " - " << prev_people << endl;
        // cout << "mul: " << to_mul << endl;
        to_add *= to_mul;

        // cout << "add: " << to_add << endl;

        ans += to_add;
    }

    cout << ans << endl;

    return 0;
}
