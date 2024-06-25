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

    long long a, b, c;
    cin >> a >> b >> c;

    long long d = 1;

    for (int i = 0; i < b; ++i) {
        d *= c;
    }

    if (a < d) cout << "Yes" << endl;
    else cout << "No" << endl;
    
    return 0;
}