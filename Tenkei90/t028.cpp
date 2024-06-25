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

int BOARD_SIZE = 1000;

int main() {

    int n;
    cin >> n;

    vector<vector<int>> cumulative_sums(BOARD_SIZE + 1, vector<int>(BOARD_SIZE + 1, 0));

    int x_left, x_right, y_bottom, y_top;

    for (int i = 0; i < n; ++i) {

        cin >> x_left >> y_bottom >> x_right >> y_top;

        cumulative_sums[x_left][y_bottom]++;
        cumulative_sums[x_right][y_top]++;
        cumulative_sums[x_left][y_top]--;
        cumulative_sums[x_right][y_bottom]--;

    }

    for (int i = 0; i < BOARD_SIZE + 1; ++i) {
        for (int j = 1; j < BOARD_SIZE + 1; ++j) {
            cumulative_sums[i][j] += cumulative_sums[i][j - 1];
        }
    }

    for (int i = 1; i < BOARD_SIZE + 1; ++i) {
        for (int j = 0; j < BOARD_SIZE + 1; ++j) {
            cumulative_sums[i][j] += cumulative_sums[i - 1][j];
        }
    }


    vector<int> areas(n + 1, 0);

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            areas[cumulative_sums[i][j]]++;
        }
    }

    for (int i = 1; i < n + 1; ++i) {
        cout << areas[i] << endl;
    }

    return 0;
}