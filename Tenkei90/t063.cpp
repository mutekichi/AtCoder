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

    for (int i = 0; i < (1 << h); ++i) {
        vector<int> usable_nums;

        for (int j = 0; j < h; ++j) {
            for (int k = 0; k < w; ++k) {
                int usable_num = -1;
                bool is_usable = true;
                if (i & (1 << j)) {
                    if (usable_num = -1) usable_num = grid[j][k];
                    else if (usable_num != grid[j][k]) is_usable = false;
                }
                if (is_usable) usable_nums.push_back(usable_num);
            }
        }

        map<int, int> usable_nums_count;
        for (auto num: usable_nums) {
            usable_nums_count[num]++;
        }

        int max_count = 0;
        for (auto p: usable_nums_count) {
            max_count = max(max_count, p.second);
        }

        ans = max(ans, max_count);
    }

    cout << ans << endl;

    return 0;
}