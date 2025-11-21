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

    int n, m, k;
    cin >> n >> m >> k;

    vector<long long> available_keys;
    vector<long long> unavailable_keys;

    for (int i = 0; i < m; ++i) {
        int c;
        cin >> c;
        long long key = 0;
        for (int k = 0; k < c; ++k) {
            int a;
            cin >> a;
            a--;
            key += (1<<a);
        }
        char r;
        cin >> r;
        if (r == 'o') {
            available_keys.push_back(key);
        } else {
            unavailable_keys.push_back(key);
        }
    }

    int ans = 0;

    for (int i = 0; i < (1<<n); ++i) {
        bool ok = true;
        for (int j = 0; j < available_keys.size(); ++j) {
            if (__builtin_popcount(i & available_keys[j]) < k) {
                ok = false;
                break;
            }
        }
        for (int j = 0; j < unavailable_keys.size(); ++j) {
            if (__builtin_popcount(i & unavailable_keys[j]) >= k) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans++;
        }
    }

    cout << ans << endl;
    
    return 0;
}