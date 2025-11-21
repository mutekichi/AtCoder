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

    int h, w;
    cin >> h >> w;

    if (h > w) swap(h, w);

    if (h == 1) {
        cout << w << endl;
        return 0;
    }

    ++h; ++w;
    cout << (h / 2) * (w / 2) << endl;
    
    return 0;
}