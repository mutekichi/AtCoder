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
    int a, b;
    a = 0;
    b = 0;
    for (int i = 0; i < 9; ++i) {
        int x;
        cin >> x; 
        a += x;
    }
    for (int i = 0; i < 8; ++i) {
        int x;
        cin >> x;
        b += x;
    }

    cout << a - b + 1 << endl;
    
    return 0;
}