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

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    int ans = 0;
    // '0' for 'f', '1' for 'fo', '2' for term
    stack<char> st;

    st.push('2');

    for (int i = 0; i < n; ++i) {
        if (s[i] == 'f') {
            st.push('0');
            ans++;
        } else if (s[i] == 'o') {
            if (st.top() == '0') {
                st.pop();
                st.push('1');
                ans++;
            } else {
                st.push('2');
                ans++;
            }
        } else if (s[i] == 'x') {
            if (st.top() == '1') {
                st.pop();
                ans = ans - 2;
            } else {
                st.push('2');
                ans++;
            }
        } else {
            st.push('2');
            ans++;
        }
    }

    cout << ans << endl;
    
    return 0;
}
