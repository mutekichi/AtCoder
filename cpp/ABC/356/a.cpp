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
    int l, r;
    cin >> l >> r;

    for (int i = 1; i <= l - 1; ++i) {
        cout << i;
        if (i != n) cout << " ";
        else cout << endl;
    }

    for (int i = l; i <= r; ++i) {
        cout << r - i + l;
        if (i != n) cout << " ";
        else cout << endl;
    }

    for (int i = r + 1; i <= n; ++i) {
        cout << i;
        if (i != n) cout << " ";
        else cout << endl;
    }
    
    return 0;
}