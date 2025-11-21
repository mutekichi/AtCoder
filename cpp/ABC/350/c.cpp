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
    int tmp;
    int ops = 0;
    cin >> n;

    vector<int> a(n);
    vector<int> b(n);

    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        a[tmp - 1] = i;
        b[i] = tmp - 1;
    }

    for (int i = 0; i < n; ++i) {
        if (a[i] == i) a[i] = -1;
        else {
            ops++;
            a[b[i]] = a[i];
            b[a[i]] = b[i];
        }
    }

    cout << ops << endl;

    for (int i = 0; i < n; ++i) {
        if (a[i] != -1) {
            cout << i + 1 << " " << a[i] + 1 << endl;
        }
    }
    

    return 0;
}