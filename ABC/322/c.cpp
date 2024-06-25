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

debug_cout dbgcout(false);


int main() {
    int n, m;
    cin >> n >> m;

    vector<int> tsugino_hanabi(n + 1, 0);

    int prev_hanabi = 0;
    int next_hanabi = 0;

    for (int i = 0; i < m; ++i) {
        prev_hanabi = next_hanabi;
        cin >> next_hanabi;
        for (int j = next_hanabi; j > prev_hanabi; --j) {
            tsugino_hanabi[j] = next_hanabi -j;
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << tsugino_hanabi[i] << endl;
    }
    
    return 0;
}