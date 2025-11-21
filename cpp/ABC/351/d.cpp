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
#include <cstdlib>

using namespace std;


int cnt;

bool moovable(vector<vector<int>> &grid, int x, int y) {
    if (x > 0 && grid[x-1][y] == -1) {
        return false;
    }
    if (x < grid.size()-1 && grid[x+1][y] == -1) {
        return false;
    }
    if (y > 0 && grid[x][y-1] == -1) {
        return false;
    }
    if (y < grid[0].size()-1 && grid[x][y+1] == -1) {
        return false;
    }
    return true;
}

void depth_first_search(vector<vector<int>> &grid, vector<vector<bool>> &visited, int x, int y) {
    if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] == -1) {
        return;
    }
    
    if (moovable(grid, x, y) == false) {
        return;
    }

    cnt++;
    visited[x][y] = true;

    depth_first_search(grid, visited, x+1, y);
    depth_first_search(grid, visited, x-1, y);
    depth_first_search(grid, visited, x, y+1);
    depth_first_search(grid, visited, x, y-1);
}

int main() {
    int h, w;
    int max = 0;

    string s;
    cin >> h >> w;

    vector<vector<int>> grid(h, vector<int>(w));
    vector<vector<bool>> visited(h, vector<bool>(w, false));

    for (int i = 0; i < h; i++) {
        cin >> s;
        for (int j = 0; j < w; j++) {
            grid[i][j] = s[j] == '#' ? -1 : 0;
        }
    }
    
    // for (int i = 0; i < h; i++) {
    //     for (int j = 0; j < w; j++) {
    //         if (grid[i][j] == -1) {
    //             cout << "#";
    //         } else if (moovable(grid, i, j)) {
    //             cout << "o";
    //         } else {
    //             cout << "x";
    //         }
    //     }
    //     cout << endl;
    // }
    // return 0;
    
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == 0) {
                depth_first_search(grid, visited, i, j);
                if (max < cnt) {
                    max = cnt;
                }
                cnt = 0;
            }
        }
    }

    cout << max << endl;

    return 0;
}