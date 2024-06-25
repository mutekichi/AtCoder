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

    vector<vector<long long>> a(3, vector<long long>(46, 0));

    long long x;

    for (long long i = 0; i < 3; ++i) {
        for (long long j = 0; j < n; ++j) {
            cin >> x;
            a[i][x % 46]++;
        }
    }

    long long ans = 0;    

    for (long long i = 0; i < 46; ++i) {
        for (long long j = 0; j < 46; ++j) {
            for (long long k = 0; k < 46; ++k) {
                if ((i + j + k) % 46 == 0) {
                    ans += a[0][i] * a[1][j] * a[2][k];
                }
            }
        }
    }

    cout << ans << endl;
    
    return 0;
}