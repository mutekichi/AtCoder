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
    int n, q;
    cin >> n >> q;

    bool haeteiru[1000];

    for (int i = 0; i < 1000; ++i) {
        haeteiru[i] = true;
    }

    for (int i = 0; i < q; ++i) {
        int ha;
        cin >> ha;
        haeteiru[ha - 1] = !haeteiru[ha - 1];
    }

    int sousuu = 0;

    for (int i = 0; i < n; ++i) {
        if (haeteiru[i]) {
            sousuu++;
        }
    }
    
    cout << sousuu << endl;

    return 0;
}