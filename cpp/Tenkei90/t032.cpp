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

    int n;
    cin >> n;

    vector<vector<int>> times(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> times[i][j];
        }
    }

    int m;
    cin >> m;
    vector<vector<bool>> is_good_relationship(n, vector<bool>(n, true));


    for (int i = 0; i < m; ++i) {
        int person1, person2;
        cin >> person1 >> person2;
        --person1; --person2;
        is_good_relationship[person1][person2] = false;
        is_good_relationship[person2][person1] = false;
    }

    vector<int> order(n);

    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }

    int min_time = INT_MAX;

    do {
        bool can_finish_race = true;
        int time = 0;
        time += times[order[0]][0];
        for (int i = 1; i < n; ++i) {
            if (!is_good_relationship[order[i - 1]][order[i]]) {
                can_finish_race = false;
                break;
            }
            else {
                time += times[order[i]][i];
            }
        }
        if (can_finish_race) {
            min_time = min(min_time, time);
        }
    } while (next_permutation(order.begin(), order.end()));

    if (min_time == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << min_time << endl;
    }
    
    return 0;
}