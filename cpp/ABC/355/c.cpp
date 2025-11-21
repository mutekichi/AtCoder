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

pair<int, int> get_masu(int a, int n) {
    int x = a / n;
    int y = a % n;
    return make_pair(x, y);
}

int is_on_taikakusen(int a, int n) {
    pair<int, int> masu = get_masu(a, n);
    if (masu.first == masu.second) {
        return 2;
    } else if (masu.first + masu.second == n - 1) {
        return 1;
    } else {
        return 0;
    }
}

int main() {

    int n, t;
    cin >> n >> t;

    vector<int> tate(n, 0);
    vector<int> yoko(n, 0);
    vector<int> taikakusen(2, 0);

    for (int i = 0; i < t; ++i) {
        int a;
        cin >> a;
        a--;
        pair<int, int> masu = get_masu(a, n);
        tate[masu.first]++;
        yoko[masu.second]++;
        if (masu.first == masu.second) {
            taikakusen[0]++;
        }
        if (masu.first + masu.second == n - 1) {
            taikakusen[1]++;
        }
        if (tate[masu.first] == n || yoko[masu.second] == n || taikakusen[0] == n || taikakusen[1] == n) {
            cout << i + 1 << endl;
            return 0;
        }
    }

    cout << -1 << endl;
    
    return 0;
}