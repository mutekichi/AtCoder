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

int main() {

    int h, w;
    cin >> h >> w;

    int rs, cs, rt, ct;
    cin >> rs >> cs >> rt >> ct;

    vector<vector<char>> grid(h + 2, vector<char>(w + 2, '#'));

    for (int i = 1; i <= h; ++i) {
        string line;
        cin >> line;
        for (int j = 1; j <= w; ++j) {
            grid[i][j] = line[j - 1];
        }
    }

    vector<pair<int, int>> directions = {
        {0, 1},
        {1, 0},
        {-1, 0},
        {0, -1}
    };

    vector<vector<vector<int>>> minimum_turns(
        h + 2,
        vector<vector<int>>(
            w + 2,
            vector<int>(4, INT_MAX)
        )
    );

    vector<vector<vector<bool>>> is_seen(
        h + 2,
        vector<vector<bool>>(
            w + 2,
            vector<bool>(4, false)
        )
    );

    deque<tuple<int, int, int>> q;

    for(int i = 0; i < 4; ++i) {
        minimum_turns[rs][cs][i] = 0;
        q.push_back(make_tuple(rs, cs, i));
    }

    while(!q.empty()) {
        tuple<int, int, int> front = q.front();
        q.pop_front();

        int r = get<0>(front);
        int c = get<1>(front);
        int d = get<2>(front);

        if (is_seen[r][c][d]) {
            continue;
        }
        is_seen[r][c][d] = true;

        for (int i = 0; i < 4; ++i) {
            if (i + d == 3) {
                continue;
            }
            int nr = r + directions[i].first;
            int nc = c + directions[i].second;
            if (grid[nr][nc] == '#') {
                continue;
            }
            if (i == d) {
                if (minimum_turns[nr][nc][i] > minimum_turns[r][c][d]) {
                    minimum_turns[nr][nc][i] = minimum_turns[r][c][d];
                    q.push_front(make_tuple(nr, nc, i));
                }
            } else {
                if (minimum_turns[nr][nc][i] > minimum_turns[r][c][d] + 1) {
                    minimum_turns[nr][nc][i] = minimum_turns[r][c][d] + 1;
                    q.push_back(make_tuple(nr, nc, i));
                }
            }
        }
    }

    int ans = INT_MAX;
    for (int i = 0; i < 4; ++i) {
        ans = min(ans, minimum_turns[rt][ct][i]);
    }

    cout << ans << endl;
    
    return 0;
}