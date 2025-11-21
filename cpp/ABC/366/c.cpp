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

debug_cout dbgcout(false);

int main() {
    int q;
    cin >> q;

    multiset<int> s_with_count;
    set<int> s_species;

    for (int i = 0; i < q; ++i) {
        int t, x;
        cin >> t;

        if (t == 1) {
            cin >> x;
            s_with_count.insert(x);
            s_species.insert(x);
        } else if (t == 2) {
            cin >> x;
            auto it = s_with_count.find(x);
            if (it != s_with_count.end()) {
                s_with_count.erase(it);
            }
            // 全て無くなれば種類も消す
            if (s_with_count.count(x) == 0) {
                s_species.erase(x);
            }
        } else if (t == 3) {
            cout << s_species.size() << endl;
        }
    }

    return 0;
}
