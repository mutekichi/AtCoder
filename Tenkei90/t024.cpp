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
    int k;

    cin >> n >> k;

    vector<int> a(n), b(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    int sum = 0;
    
    for (int i = 0; i < n; ++i) {
        sum += abs(a[i] - b[i]);
    }

    if (sum <= k && (k - sum) % 2 == 0) cout << "Yes" << endl;
    else cout << "No" << endl;
    
    return 0;
}