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

bool check_char_small(char c) {
    return 'a' <= c && c <= 'z';
}

char to_upper(char c) {
    return c - 'a' + 'A';
}

char to_lower(char c) {
    return c - 'A' + 'a';
}

debug_cout dbgcout(true);

int main() {

    string s;
    cin >> s;

    int count = 0;

    for (int i = 0; i < s.size(); ++i) {
        if (check_char_small(s[i])) {
            count++;
        }
    }

    if (count > s.size() - count) {
        for (int i = 0; i < s.size(); ++i) {
            if (check_char_small(s[i])) {
                cout << s[i];
            }
            else {
                cout << to_lower(s[i]);
            }
        }
    }
    else {
        for (int i = 0; i < s.size(); ++i) {
            if (check_char_small(s[i])) {
                cout << to_upper(s[i]);
            }
            else {
                cout << s[i];
            }
        }
    }

    cout << endl;
    
    return 0;
}