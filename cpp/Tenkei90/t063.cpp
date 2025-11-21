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

    vector<vector<int>> grid(h, vector<int>(w));

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> grid[i][j];
        }
    }

    int ans = 0;

    for (int i = 0; i < (1 << h); i++) {
        map<int, int> mp;

        for (int j = 0; j < w; ++j) {
            int num = -1;
            for (int k = 0; k < h; ++k) {
                if (i & (1 << k)) {
                    if (num == -1) {
                        num = grid[k][j];
                    } else if (num != grid[k][j]) {
                        num = -2;
                        break;
                    } else {
                        continue;
                    }
                }
            }
            if (num >= 0) {
                mp[num]++;
            }
        }

        for (auto p : mp) {
            ans = max(ans, p.second * __builtin_popcount(i));
        }
    }

    cout << ans << endl;

    return 0;
}