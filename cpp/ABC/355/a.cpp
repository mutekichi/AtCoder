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

    int a, b;
    cin >> a >> b;

    if (a != b) {
        if (a > b) swap(a, b);
        if (a == 1) {
            if (b == 2) cout << 3 << endl;
            else cout << 2 << endl;
        }
        if (a == 2) cout << 1 << endl;
    } else cout << -1 << endl;
    
    return 0;
}