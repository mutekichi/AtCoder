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

bool check_is_kaibun(string s) {
    for (int i = 0; i < s.size() / 2; i++) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}



int main() {

    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = i;
    }


    long long ans = 0;

    set<string> str_not_including_length_k_kaibun;
    
    do {
        string t = s;

        for (int i = 0; i < n; ++i) {
            t[i] = s[v[i]];
        }

        bool include_k_kaibun = false;

        for (int i = 0; i < n - k + 1; ++i) {
            string u = t.substr(i, k);
            if (check_is_kaibun(u)) {
                include_k_kaibun = true;
                break;
            }
        }

        if (!include_k_kaibun) {
            str_not_including_length_k_kaibun.insert(t);
        }


    } while (next_permutation(v.begin(), v.end()));

    cout << str_not_including_length_k_kaibun.size() << endl;


    return 0;
}
