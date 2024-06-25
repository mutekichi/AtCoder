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

int msb(long long h) {
    int msb = 0;
    while (h > 0) {
        h >>= 1;
        msb++;
    }
    return msb;
}

int main() {

    long long h;

    cin >> h;

    cout << msb(h + 1) << endl;
    
    return 0;
}