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

    long long n;
    cin >> n;
    int k;
    cin >> k;

    vector<int> factors(n, 0);

    for (int i = 2; i <= n; ++i) {
        if (factors[i] != 0) continue;
        for (int j = i; j <= n; j += i) {
            factors[j]++;
        }
    }

    long long ans = 0;

    for (int i = 2; i <= n; ++i) {
        if (factors[i] >= k) ans++;
    }

    cout << ans << endl;
    
    return 0;
}