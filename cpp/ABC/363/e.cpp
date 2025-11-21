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

    int h, w, height_y;
    cin >> h >> w >> height_y;

    vector<vector<int>> grid(h + 2, vector<int>(w + 2));

    set<tuple<int, int, int>> to_check;

    int max_height = height_y + 1;

    // cout << max_height << endl;

    for (int i = 0; i < h + 2; i++) {
        for (int j = 0; j < w + 2; j++) {
            if (i == 0 || i == h + 1 || j == 0 || j == w + 1) {
                grid[i][j] = max_height;
            } else {
                int height;
                cin >> height;
                if (height > max_height) grid[i][j] = max_height;
                else grid[i][j] = height;   
            }

            if (i == 1 || i == h || j == 1 || j == w) {
                if (i != 0 && i != h + 1 && j != 0 && j != w + 1) {
                    to_check.insert(make_tuple(grid[i][j], i, j));
                }
            }
        }
    }

    // for (int i = 0; i < h + 2; i++) {
    //     for (int j = 0; j < w + 2; j++) {
    //         cout << grid[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    long long sinked = 0;

    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    for (int i = 1; i <= height_y; ++i) {
        while (!to_check.empty() && get<0>(*to_check.begin()) <= i) {
            auto it = *to_check.begin();
            int x = get<1>(it);
            int y = get<2>(it);
            to_check.erase(to_check.begin());

            // cout << x << " " << y << " " << grid[x][y] << endl;

            sinked++;
            grid[x][y] = max_height;
                    
            for (auto d : directions) {
                int dx = d.first;
                int dy = d.second;

                int nx = x + dx;
                int ny = y + dy;

                if (grid[nx][ny] != max_height) {
                    to_check.insert(make_tuple(grid[nx][ny], nx, ny));
                }
            }
        }
        cout << h * w - sinked << endl;
    }


    return 0;
}
