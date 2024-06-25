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

    vector<vector<int>> a(h, vector<int>(w));

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cin >> a[i][j];
        }
    }

    vector<int> row_sum(h), column_sum(w);

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            row_sum[i] += a[i][j];
            column_sum[j] += a[i][j];
        }
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (j != 0) cout << " ";
            cout << row_sum[i] + column_sum[j] - a[i][j];
        }
        if (i != h - 1) cout << endl;
    }
    
    return 0;
}