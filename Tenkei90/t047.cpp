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
#include <cstdlib>

using namespace std;

const unsigned long long MOD = (1ll<<61) - 1ll;
const unsigned long long MASK30 = (1ll<<30) - 1ll;
const unsigned long long MASK31 = (1ll<<31) - 1ll;
const unsigned long long POSITIVISER = MOD * 4ll;


unsigned long long calc_mod(unsigned long long a) {
    a = (a & MOD) + (a >> 61);
    if (a >= MOD) {
        a -= MOD;
    }
    return a;
}

unsigned long long mod_multiply(unsigned long long a, unsigned long long b) {
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
    vector<unsigned long long>& mod_table,
    unsigned long long base,
    int n
) {
    mod_table[0] = 1;
    for (int i = 1; i <= n; ++i) {
        mod_table[i] = calc_mod(mod_multiply(mod_table[i - 1], base));
    }
}

void calc_hash_table(
    vector<unsigned long long>& hash_table,
    const string& s,
    const vector<unsigned long long>& mod_table,
    unsigned long long base
) {
    hash_table[0] = 0;
    for (int i = 0; i < s.size(); ++i) {
        hash_table[i + 1] = calc_mod(mod_multiply(hash_table[i], base) + s[i]);
    }
}

unsigned long long calc_hash_substring(
    const vector<unsigned long long>& hash_table,
    const vector<unsigned long long>& mod_table,
    unsigned long long base,
    int l,
    int r
) {
    return calc_mod(hash_table[r] + POSITIVISER - mod_multiply(hash_table[l], mod_table[r - l]));
}

unsigned long long calc_hash(
    const string& s,
    unsigned long long base,
    const vector<unsigned long long>& mod_table = vector<unsigned long long>()
) {
    if (mod_table.empty()) {
        vector<unsigned long long> mod_table(s.size() + 1);
        calc_mod_table(mod_table, base, s.size());
    }
    unsigned long long hash = 0;
    for (int i = 0; i < s.size(); ++i) {
        hash = calc_mod(mod_multiply(hash, base) + s[i]);
    }
    return hash;
}

class RollingHash {
public:
    vector<unsigned long long> hash_table;
    vector<unsigned long long> mod_table;
    unsigned long long base;

    RollingHash(const string& s, unsigned long long base) {
        this->base = base;
        mod_table.resize(s.size() + 1);
        hash_table.resize(s.size() + 1);
        calc_mod_table(mod_table, base, s.size());
        calc_hash_table(hash_table, s, mod_table, base);
    }

    unsigned long long get(int l, int r) {
        return calc_hash_substring(hash_table, mod_table, base, l, r);
    }
};

string substr_string(string s, vector<pair<char, char>> substr) {
    string res = s;

    for (int i = 0; i < s.size(); ++i) {
        for (int j = 0; j < substr.size(); ++j) {
            if (s[i] == substr[j].first) {
                res[i] = substr[j].second;
            }
        }
    }

    return res;
}

int main() {

    int n;
    cin >> n;

    string s;
    string t;
    
    cin >> s >> t;

    string t_R = substr_string(t, {make_pair('G', 'B'), make_pair('B', 'G')});
    string t_G = substr_string(t, {make_pair('B', 'R'), make_pair('R', 'B')});
    string t_B = substr_string(t, {make_pair('R', 'G'), make_pair('G', 'R')});

    RollingHash rh_s(s, 1009);
    RollingHash rh_t_R(t_R, 1009);
    RollingHash rh_t_G(t_G, 1009);
    RollingHash rh_t_B(t_B, 1009);

    int ans = 0;

    for (int i = 1; i < n; ++i) {
        unsigned long long hash_s = rh_s.get(n - i, n);
        unsigned long long hash_t_R = rh_t_R.get(0, i);
        unsigned long long hash_t_G = rh_t_G.get(0, i);
        unsigned long long hash_t_B = rh_t_B.get(0, i);
        if (hash_s == hash_t_R || hash_s == hash_t_G || hash_s == hash_t_B) {
            ans += 1;
        }
    }

    if (s == t_R || s == t_G || s == t_B) {
        ans += 1;
    }

    for (int i = 1; i < n; ++i) {
        unsigned long long hash_s = rh_s.get(0, i);
        unsigned long long hash_t_R = rh_t_R.get(n - i, n);
        unsigned long long hash_t_G = rh_t_G.get(n - i, n);
        unsigned long long hash_t_B = rh_t_B.get(n - i, n);
        if (hash_s == hash_t_R || hash_s == hash_t_G || hash_s == hash_t_B) {
            ans += 1;
        }
    }

    cout << ans << endl;
    
    return 0;
}