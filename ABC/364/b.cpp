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

    int h, w;
    cin >> h >> w;

    int si, sj;
    cin >> si >> sj;

    vector<vector<bool>> grid(h + 2, vector<bool>(w + 2, false));

    for (int i = 1; i <= h; ++i) {
        string s;
        cin >> s;
        for (int j = 1; j <= w; ++j) {
            grid[i][j] = s[j - 1] == '.';
        }
    }

    string operations;
    cin >> operations;

    for (int i = 0; i < operations.size(); ++i) {
        int di = 0, dj = 0;
        if (operations[i] == 'U') {
            di = -1;
        } else if (operations[i] == 'D') {
            di = 1;
        } else if (operations[i] == 'L') {
            dj = -1;
        } else if (operations[i] == 'R') {
            dj = 1;
        }

        if (grid[si + di][sj + dj]) {
            si += di;
            sj += dj;
        }
    }

    cout << si << " " << sj << endl;

    
    return 0;
}
