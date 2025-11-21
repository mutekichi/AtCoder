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

int pow(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}   

debug_cout dbgcout(true);



void make_string_level_k(int level, vector<vector<char>> &s, int h_start, int w_start) {
    if (level == 0) {
        s[h_start][w_start] = '#';
        return;
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == 1 && j == 1) {
                continue;
            } else {
                make_string_level_k(level - 1, s, h_start + i * pow(3, level - 1), w_start + j * pow(3, level - 1));
            }
        }
    }
}

int main() {

    int n;
    cin >> n;

    int size = pow(3, n);

    vector<vector<char>> s(size, vector<char>(size, '.'));

    make_string_level_k(n, s, 0, 0);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << s[i][j];
        }
        cout << endl;
    }
    
    return 0;
}