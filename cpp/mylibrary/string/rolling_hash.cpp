#include <iostream>
#include <vector>

using namespace std;

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
        calc_mod_table(mod_table, base, s.size());
    }
    unsigned long long hash = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        hash = calc_mod(mod_multiply(hash, base) + s[i]);
    }
    return hash;
}

class RollingHash
{
public:
    vector<unsigned long long> hash_table;
    vector<unsigned long long> mod_table;
    unsigned long long base;

    RollingHash(const string &s, unsigned long long base)
    {
        this->base = base;
        mod_table.resize(s.size() + 1);
        hash_table.resize(s.size() + 1);
        calc_mod_table(mod_table, base, s.size());
        calc_hash_table(hash_table, s, mod_table, base);
    }

    unsigned long long get(int l, int r)
    {
        return calc_hash_substring(hash_table, mod_table, base, l, r);
    }
};

int main()
{

    string s = "abcdebcdefg";
    string t = "bcd";

    RollingHash rh(s, 27);

    unsigned long long hash_t = calc_hash(t, 27);

    for (int i = 0; i + t.size() <= s.size(); ++i)
    {
        if (rh.get(i, i + t.size()) == hash_t)
        {
            cout << i << endl;
        }
    }

    // unsigned long long base = 27;

    // vector<unsigned long long> mod_table(t.size() + 1);
    // vector<unsigned long long> hash_table(s.size() + 1);

    // calc_mod_table(mod_table, base, t.size());
    // calc_hash_table(hash_table, s, mod_table, base);

    // unsigned long long hash_t = 0;
    // for (int i = 0; i < t.size(); ++i) {
    //     hash_t = calc_mod(mod_multiply(hash_t, base) + t[i]);
    // }

    // for (int i = 0; i + t.size() <= s.size(); ++i) {
    //     if (calc_hash_substring(hash_table, mod_table, base, i, i + t.size()) == hash_t){
    //         cout << i << endl;
    //     }
    // }

    return 0;
}