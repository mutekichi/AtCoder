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

debug_cout dbgcout(false);

template<typename T>
void print_vector(vector<T> v, bool debug) {
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

struct point {
    int x, y;
};

double pow_2(double x) {
    return x * x;
}

int main() {

    int n, s, t;
    cin >> n >> s >> t;

    vector<pair<point, point>> lines(n);
    for (int i = 0; i < n; i++) {
        cin >> lines[i].first.x >> lines[i].first.y >> lines[i].second.x >> lines[i].second.y;
    }

    vector<int> permutation(n);

    for (int i = 0; i < n; i++) {
        permutation[i] = i;
    }

    long double ans_min = 1e9;

    long double lines_length_sum = 0;
    for (int i = 0; i < n; i++) {
        lines_length_sum += sqrt(pow_2(lines[i].first.x - lines[i].second.x) + pow_2(lines[i].first.y - lines[i].second.y));
    }

    point init_point = {0, 0};
    point current_point = init_point;

    int cnt = 0;

    do {
        for (int i = 0; i < (1 << n); ++i) {
            long double total_dist = 0;
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    total_dist += sqrt(pow_2(current_point.x - lines[permutation[j]].first.x) + pow_2(current_point.y - lines[permutation[j]].first.y));
                    dbgcout << "from: " << current_point.x << " " << current_point.y << endl;
                    dbgcout << "to: " << lines[permutation[j]].first.x << " " << lines[permutation[j]].first.y << endl;
                    current_point = lines[permutation[j]].second;
                }
                else {
                    total_dist += sqrt(pow_2(current_point.x - lines[permutation[j]].second.x) + pow_2(current_point.y - lines[permutation[j]].second.y));
                    dbgcout << "from: " << current_point.x << " " << current_point.y << endl;
                    dbgcout << "to: " << lines[permutation[j]].second.x << " " << lines[permutation[j]].second.y << endl;
                    current_point = lines[permutation[j]].first;
                }
            }
            ans_min = min(ans_min, total_dist);
            current_point = init_point;
        }

    } while (next_permutation(permutation.begin(), permutation.end()));


    cout << fixed << setprecision(10) << ans_min / (long double)s + lines_length_sum / (long double)t << endl;

    return 0;
}
