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

    int n, m;
    cin >> n >> m;

    int a;

    vector<pair<int, char>> c(n + m);

    for (int i = 0; i < n; ++i) {
        cin >> a;
        c.push_back(make_pair(a, 'a'));
    }
    for (int j = 0; j < m; ++j) {
        cin >> a;
        c.push_back(make_pair(a, 'b'));
    }

    sort(c.begin(), c.end(), greater<pair<int, char>>());

    for(int i = 0; i < n + m - 1; ++i) {
        // cout << c[i].first << " " << c[i].second << endl;
        if (c[i].second == 'a' && c[i + 1].second == 'a') {
            cout << "Yes" << endl;
            return 0;
        }
    }

    cout << "No" << endl;
    
    return 0;
}