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
    vector<int> a(n);
    int tmp;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        a[tmp - 1] = i;
    }
    int q;
    cin >> q;

    int a, b;

    for (int i = 0; i < q; ++i) {
        cin >> a >> b;
        
    }
    
    return 0;
}