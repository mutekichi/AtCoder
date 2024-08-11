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

int main() {
    int max_length = 100;
    int n;
    cin >> n;
    vector<string> sentence(n);

    int max_sentence_length = 0;
    for (int i = 0; i < n; i++) {
        cin >> sentence[i];
        max_sentence_length = max(max_sentence_length, (int)sentence[i].length());
        for (int j = sentence[i].length(); j < max_length; j++) {
            sentence[i] += "*";
        }
    }

    for (int i = 0; i < max_sentence_length; ++i) {
        int len = 0;
        for (int j = 0; j < n; ++j) {
            if (sentence[j][i] != '*') {
                len = n - j;
                break;
            }
        }
        for (int j = 0; j < len; ++j) {
            cout << sentence[n - j - 1][i];
        }
        cout << endl;
    }

    return 0;
}
