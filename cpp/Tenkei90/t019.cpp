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

int INF = 1e9;

int main() {

    int n;
    cin >> n;

    vector<int> a(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> a[i];
    }

    // vector<vector<int>> dp(2 * n, vector<int>(2 * n, 0));

    // for (int i = 1; i < 2 * n; i = i + 2) {
    //     for (int j = 0; j < 2 * n - i; ++j) {
    //         if (i == 1) {
    //             dp[j][i + j] = abs(a[j] - a[i + j]);
    //         } else {
    //             int pattern1 = abs(a[j] - a[j +i]) + dp[j + 1][j + i - 1];
    //             int pattern2 = INF;
    //             for (int k = 1; k < i; k = k + 2) {
    //                 pattern2 = min(dp[j][j + k] + dp[j + k][i + j], pattern2);
    //             }
    //             dp[j][i + j] = min(pattern1, pattern2);
    //         }
    //     }
    // }

    // for (int i = 1; i < 2 * n; i = i + 2) {
    //     for (int j = 0; j < 2 * n; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // cout << dp[0][2 * n - 1] << endl;

    vector<vector<int>> dp(n, vector<int>(2 * n - 1, INF));

    for (int width = 0; width < n; ++width) {
        for (int left = 0; left < 2 * n - 1 - 2 * width; ++left) {
            if (width == 0) {
                dp[width][left] = abs(a[left] - a[left + 1]);                
            } else {
                dp[width][left] = abs(a[left] - a[left + 2 * width + 1]) + dp[width - 1][left + 1];
                for (int inner_width = 0; inner_width < width; ++inner_width) {
                    dp[width][left] = min(dp[width][left], dp[inner_width][left] + dp[width - inner_width - 1][left + 2 * (inner_width + 1)]);
                }
            }
        }
    }

    cout << dp[n - 1][0] << endl;
      
    return 0;
}