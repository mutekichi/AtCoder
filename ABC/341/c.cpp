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

debug_cout dbgcout(true);

int main() {

    int h, w;
    cin >> h >> w;
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<vector<char>> grid(h, vector<char>(w));

    for (int i = 0; i < h; ++i) {
        string row;
        cin >> row;
        for (int j = 0; j < w; ++j) {
            grid[i][j] = row[j];
        }
    }

    int ans = 0;

    

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int x = i;
            int y = j;
            bool ok = true;
            for (int k = 0; k < n; ++k) {
                if (grid[x][y] == '#') {
                    ok = false;
                    break;
                }
                if (s[k] =='U') x--;
                if (s[k] =='D') x++;
                if (s[k] =='L') y--;
                if (s[k] =='R') y++;
            }
            if (grid[x][y] == '#') ok = false;
            if (ok) ans++;
        }
    }

    cout << ans << endl;
    
    return 0;
}
