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

    int n, x, y, z;

    cin >> n >> x >> y >> z;

    if ((x < z && z < y) || (y < z && z < x)) {
        cout << "Yes" << endl;
    } else cout << "No" << endl;
    
    return 0;
}