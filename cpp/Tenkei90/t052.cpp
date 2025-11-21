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
    long long mod = 1000000007;

    long long ans = 1ll;

    for (int i = 0; i < n; ++i) {
        long long dice_sum = 0;
        for (int j = 0; j < 6; ++j) {
            long long dice;
            cin >> dice;
            dice_sum += dice;
        }
        ans *= dice_sum;
        ans %= mod;
    }
    
    cout << ans << endl;

    return 0;
}