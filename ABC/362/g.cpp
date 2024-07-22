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

class debug_cout {
public:
    debug_cout(bool debug) : debug(debug) {}

    template<typename T>
    debug_cout& operator<<(const T& value) {
        if (debug) {
            cout << value;
        }
        return *this;
    }

    debug_cout& operator<<(std::ostream& (*manip)(std::ostream&)) {
        if (debug) {
            manip(std::cout);
        }
        return *this;
    }

private:
    bool debug;
};

template<typename T>
void print_vector(vector<T> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

debug_cout dbgcout(true);


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




int main() {
    string s;
    int q;
    cin >> s >> q;

    RollingHash rh(s, 27);

    set<int> query_lengths;
    map<int, vector<pair<unsigned long long, int>>> hashed_queries_with_string_length;

    for (int i = 0; i < q; ++i) {
        string query;
        cin >> query;

        unsigned long long hashed_query = calc_hash(query, 27);
        int query_length = query.size();
        if (query_lengths.find(query_length) == query_lengths.end()) {
            query_lengths.insert(query_length);
            hashed_queries_with_string_length[query_length] = vector<pair<unsigned long long, int>>();
        }

        hashed_queries_with_string_length[query_length].push_back(make_pair(hashed_query, i));
    }

    vector<int> answers(q, 0);

    for (int query_length: query_lengths) {
        map<unsigned long long, int> hashes_with_count;
        for (int i = 0; i < s.size() - query_length + 1; ++i) {
            unsigned long long hashed_substring = rh.get(i, i + query_length);
            if (hashes_with_count.find(hashed_substring) == hashes_with_count.end()) {
                hashes_with_count[hashed_substring] = 0;
            }
            hashes_with_count[hashed_substring]++;
        }
        for (auto itr = hashed_queries_with_string_length[query_length].begin(); itr != hashed_queries_with_string_length[query_length].end(); ++itr) {
            unsigned long long hashed_query = itr->first;
            int query_index = itr->second;
            if (hashes_with_count.find(hashed_query) != hashes_with_count.end()) {
                answers[query_index] = hashes_with_count[hashed_query];
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        cout << answers[i] << endl;
    }
    
    return 0;
}
