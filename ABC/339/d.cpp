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

debug_cout dbgcout(true);

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

int main() {

    int n;
    cin >> n;
    vector<vector<bool>> grid(n + 2, vector<bool>(n + 2, false));

    pair<int, int> start1;
    pair<int, int> start2;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            if (c == '.') {
                grid[i][j] = true;
            }
            else if (c == 'P') {
                if (start1.first == 0) {
                    start1 = make_pair(i, j);
                }
                else {
                    start2 = make_pair(i, j);
                }
                grid[i][j] = true;
            }
            else {
                grid[i][j] = false;
            }
        }
    }

    vector<vector<vector<vector<int>>>> min_steps(
        n + 2, vector<vector<vector<int>>>(
            n + 2, vector<vector<int>>(
                n + 2, vector<int>(n + 2, INT_MAX)
            )
        )
    );

    queue<tuple<int, int, int, int>> q;
    
    q.push(make_tuple(start1.first, start1.second, start2.first, start2.second));
    min_steps[start1.first][start1.second][start2.first][start2.second] = 0;

    while(!q.empty()) {
        auto qf = q.front();
        int x1 = get<0>(qf);
        int y1 = get<1>(qf);
        int x2 = get<2>(qf);
        int y2 = get<3>(qf);
        q.pop();

        // dbgcout << "x1: " << x1 << ", y1: " << y1 << ", x2: " << x2 << ", y2: " << y2 << endl;

        if (x1 == x2 && y1 == y2) {
            cout << min_steps[x1][y1][x2][y2] << endl;
            return 0;
        }

        vector<pair<int, int>> directions = {
            make_pair(0, 1),
            make_pair(0, -1),
            make_pair(1, 0),
            make_pair(-1, 0)
        };

        for (auto d: directions) {
            int dx = d.first;
            int dy = d.second;

            int nx1 = grid[x1 + dx][y1 + dy] ? x1 + dx : x1;
            int ny1 = grid[x1 + dx][y1 + dy] ? y1 + dy : y1;
            int nx2 = grid[x2 + dx][y2 + dy] ? x2 + dx : x2;
            int ny2 = grid[x2 + dx][y2 + dy] ? y2 + dy : y2;

            if (min_steps[nx1][ny1][nx2][ny2] == INT_MAX) {
                min_steps[nx1][ny1][nx2][ny2] = min_steps[x1][y1][x2][y2] + 1;
                q.push(make_tuple(nx1, ny1, nx2, ny2));
            }
        }
    }

    cout << -1 << endl;

    return 0;
}
