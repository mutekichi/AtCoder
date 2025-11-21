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

debug_cout dbgcout(true);

template<typename T>
void output_vector(vector<T> v, bool debug) {
    for (int i = 0; i < v.size(); i++) {
        if (debug) {
            dbgcout << v[i] << " ";
        }
        else {
            cout << v[i] << " ";
        }
    }
    if (debug) {
        dbgcout << endl;
    }
    else {
        cout << endl;
    }
}

int solve(vector<int> &vec) {
    int n = vec.size();
    if (n == 0) {
        return 0;
    }
    set<int> st;
    int cur_size = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (st.find(vec[i]) == st.end()) {
            st.insert(vec[i]);
            cur_size++;
            ans = max(ans, cur_size);
        }
        else {
            if (vec[i - cur_size] == vec[i]) {
                continue;
            }
            else {
                while(vec[i - cur_size] != vec[i]) {
                    st.erase(vec[i - cur_size]);
                    cur_size--;
                }
            }
        }
    }
    
    return ans;
}

int main() {

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int index = 0;

    vector<int> vec;

    int ans = 0;

    while(true) {
        if (a[index] == a[index + 1] && index + 1 < n) {
            vec.push_back(a[index]);
            index += 2;
            continue;
        }
        else {
            ans = max(ans, solve(vec));
            vec = {};
            if (index > 0 && a[index - 1] == a[index]) {
                vec.push_back(a[index]);
            }
            index++;
        }

        if (index >= n) {
            ans = max(ans, solve(vec));
            break;
        }
    }

    cout << ans * 2 << endl;

    return 0;
}


