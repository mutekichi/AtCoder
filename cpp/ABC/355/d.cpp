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
#include <iomanip>

using namespace std;

int main() {

    int n;
    cin >> n;

    vector<pair<long long, int>> list;

    for (int i = 0; i < n; ++i) {
        long long a, b;
        cin >> a >> b;
        list.push_back(make_pair(a, 0));
        list.push_back(make_pair(b, 1));
    }

    sort(list.begin(), list.end(), less<pair<long long, int>>());

    long long ans = 0;
    long long lefts = 0;

    // for (int i = 0; i < 2 * n; ++i) {
    //     cout << list[i].first << " " << list[i].second << endl;
    // }

    for (int i = 0; i < 2 * n; ++i) {
        if (list[i].second == 0) {
            lefts++;
        } else {
            if (lefts > 0) ans += --lefts;
        }
        // cout << ans << endl;
    }

    cout << ans << endl;
    
    return 0;
}