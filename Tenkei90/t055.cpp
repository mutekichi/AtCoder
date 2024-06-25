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

long long ans = 0;
int n;
long long p, q;
vector<long long> a(100);

int main() {

    cin >> n >> p >> q;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] %= p;
    }

    for (int i = 0; i < n - 4; ++i) {
        long long temp1 = a[i];
        temp1 %= p;
        for (int j = i + 1; j < n - 3; ++j) {
            long long temp2 = temp1 * a[j];
            temp2 %= p;
            for (int k = j + 1; k < n - 2; ++k) {
                long long temp3 = temp2 * a[k];
                temp3 %= p;
                for (int l = k + 1; l < n - 1; ++l) {
                    long long temp4 = temp3 * a[l];
                    temp4 %= p;
                    for (int m = l + 1; m < n; ++m) {
                        long long temp5 = temp4 * a[m];
                        temp5 %= p;
                        if (temp5 == q) {
                            ++ans;
                        }
                    }
                }
            }
        }
    } cout << ans << endl;
    
    return 0;
}