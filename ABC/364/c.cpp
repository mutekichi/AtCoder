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

    int n;
    cin >> n;

    long long sweet_lim, salty_lim;
    cin >> sweet_lim >> salty_lim;

    vector<long long> sweet(n);
    vector<long long> salty(n);

    for (int i = 0; i < n; ++i) {
        cin >> sweet[i];
    }

    sort(sweet.begin(), sweet.end(), greater<long long>());

    for (int i = 0; i < n; ++i) {
        cin >> salty[i];
    }

    sort(salty.begin(), salty.end(), greater<long long>());

    long long current_sweet = 0;
    int sweet_num;

    for (int i = 0; i < n; ++i) {
        current_sweet += sweet[i];
        if (current_sweet >= sweet_lim) {
            sweet_num = i + 1;
            break;
        }
        if (i == n - 1) {
            sweet_num = n;
        }
    }

    long long current_salty = 0;
    int salty_num;

    for (int i = 0; i < n; ++i) {
        current_salty += salty[i];
        if (current_salty >= salty_lim) {
            salty_num = i + 1;
            break;
        }
        if (i == n - 1) {
            salty_num = n;
        }
    }

    cout << min(sweet_num, salty_num) << endl;


}
