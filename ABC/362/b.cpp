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

bool is_right_angle(vector<int> x_list, vector<int> y_list) {
    vector<int> x_diff(3);
    vector<int> y_diff(3);

    for (int i = 0; i < 3; i++) {
        x_diff[i] = x_list[(i + 1) % 3] - x_list[i];
        y_diff[i] = y_list[(i + 1) % 3] - y_list[i];
    }

    for (int i = 0; i < 3; i++) {
        if (x_diff[i] * x_diff[(i + 1) % 3] + y_diff[i] * y_diff[(i + 1) % 3] == 0) {
            return true;
        }
    }

    return false;
}

int main() {

    vector<int> x_list(3);
    vector<int> y_list(3);

    for (int i = 0; i < 3; i++) {
        cin >> x_list[i] >> y_list[i];
    }

    if (is_right_angle(x_list, y_list)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }


    
    return 0;
}
