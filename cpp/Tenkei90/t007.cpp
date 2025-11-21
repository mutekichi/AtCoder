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

const unsigned long long INF = 1LL << 60;

unsigned long long calc_frustration(set<unsigned long long> &classes, unsigned long long ability) {
    auto iter = classes.lower_bound(ability);

    if (iter == classes.begin()) {
        return min(INF, *classes.begin() - ability);
    } else if (iter == --classes.end()) {
        return min(INF, ability - *--classes.end());
    } else {
        unsigned long long ikkoue = *iter;
        unsigned long long ikkoshita = *--iter;

        return min(INF,min(ikkoue - ability, ability - ikkoshita));
    }
}

int main() {

    int n;
    cin >> n;

    set<unsigned long long> classes;

    unsigned long long a;
    for (int i = 0; i < n; ++i) {
        cin >> a;
        classes.insert(a);
    }

    int q;
    cin >> q;

    unsigned long long ability;

    for (int i = 0; i < q; ++i) {
        cin >> ability;
        cout << calc_frustration(classes, ability) << endl;
    }
    
    return 0;
}