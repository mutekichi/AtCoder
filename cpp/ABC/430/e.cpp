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

const unsigned long long MOD = (1ll << 61) - 1ll;
const unsigned long long MASK30 = (1ll << 30) - 1ll;
const unsigned long long MASK31 = (1ll << 31) - 1ll;
const unsigned long long POSITIVISER = MOD * 4ll;

unsigned long long calc_mod(unsigned long long a)
{
    a = (a & MOD) + (a >> 61);
    if (a >= MOD)
    {
        a -= MOD;
    }
    return a;
}

unsigned long long mod_multiply(unsigned long long a, unsigned long long b)
{
    unsigned long long au = a >> 31;
    unsigned long long ad = a & MASK31;
    unsigned long long bu = b >> 31;
    unsigned long long bd = b & MASK31;
    unsigned long long mid = ad * bu + au * bd;
    unsigned long long midu = mid >> 30;
    unsigned long long midd = mid & MASK30;
    return au * bu * 2 + midu + (midd << 31) + ad * bd;
}

void calc_mod_table(
    vector<unsigned long long> &mod_table,
    unsigned long long base,
    int n)
{
    mod_table[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        mod_table[i] = calc_mod(mod_multiply(mod_table[i - 1], base));
    }
}

void calc_hash_table(
    vector<unsigned long long> &hash_table,
    const string &s,
    const vector<unsigned long long> &mod_table,
    unsigned long long base)
{
    hash_table[0] = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        hash_table[i + 1] = calc_mod(mod_multiply(hash_table[i], base) + s[i]);
    }
}

unsigned long long calc_hash_substring(
    const vector<unsigned long long> &hash_table,
    const vector<unsigned long long> &mod_table,
    unsigned long long base,
    int l,
    int r)
{
    return calc_mod(hash_table[r] + POSITIVISER - mod_multiply(hash_table[l], mod_table[r - l]));
}

unsigned long long calc_hash(
    const string &s,
    unsigned long long base,
    const vector<unsigned long long> &mod_table = vector<unsigned long long>())
{
    if (mod_table.empty())
    {
        vector<unsigned long long> mod_table(s.size() + 1);
        calc_mod_table(mod_table, base, s.size() + 1);
    }
    unsigned long long hash = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        hash = calc_mod(mod_multiply(hash, base) + (s[i] == '1' ? 1 : 0));
    }
    return hash;
}

unsigned long long base = 2ull;

unsigned long long base2 = 3ull;

int main()
{
    int t;
    cin >> t;

    vector<unsigned long long> mod_table(1000005);
    calc_mod_table(mod_table, base, 1000005);

    vector<unsigned long long> mod_table2(1000005);
    calc_mod_table(mod_table2, base2, 1000005);

    for (int tn = 0; tn < t; ++tn)
    {
        string a, b;
        cin >> a >> b;
        // reverse(a.begin(), a.end());
        // reverse(b.begin(), b.end());
        int size = (int)(a.size());
        // cout << "size : " << size << endl;
        unsigned long long a_hash = calc_hash(a, base, mod_table);
        unsigned long long b_hash = calc_hash(b, base, mod_table);

        unsigned long long a_hash2 = calc_hash(a, base2, mod_table2);
        unsigned long long b_hash2 = calc_hash(b, base2, mod_table2);

        int ans = -1;

        // cout << "case starts:" << endl;
        // cout << a_hash << endl;
        // cout << b_hash << endl
        //      << endl;

        // cout << " a : " << a << endl;

        for (int i = 0; i < size; ++i)
        {
            // cout << "a_hash " << a_hash << endl;
            if (a_hash == b_hash && a_hash2 == b_hash2)
            {
                ans = i;
                break;
            }
            else
            {
                // cout << "char: " << a[size - 1 - i] << endl;
                if (a[i] == '1')
                {
                    a_hash += POSITIVISER;
                    a_hash -= mod_table[size - 1];
                    a_hash %= MOD;
                    // cout << "here: " << a_hash << endl;
                    a_hash = mod_multiply(a_hash, base);
                    a_hash += 1ll;
                    a_hash %= MOD;
                    // cout << "afte: " << a_hash << endl;

                    a_hash2 += POSITIVISER;
                    a_hash2 -= mod_table2[size - 1];
                    a_hash2 %= MOD;
                    // cout << "here: " << a_hash << endl;
                    a_hash2 = mod_multiply(a_hash2, base2);
                    a_hash2 += 1ll;
                    a_hash2 %= MOD;
                }
                else
                {
                    a_hash = mod_multiply(a_hash, base);
                    a_hash %= MOD;

                    a_hash2 = mod_multiply(a_hash2, base2);
                    a_hash2 %= MOD;
                }
            }
        }
        cout << ans << endl;
    }

    return 0;
}
