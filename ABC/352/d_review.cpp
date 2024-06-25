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

int get_range(set<int> &set_p) {
    int min_p = *set_p.begin();
    int max_p = *set_p.rbegin();

    return max_p - min_p;
};

int main() {

    int n, k;

    cin >> n >> k;

    vector<int> a(n);
    int tmp;

    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        a[tmp - 1] = i;
    }

    set<int> set_p;

    for (int i = 0; i < k; ++i) {
        set_p.insert(a[i]);
    }

    int range = get_range(set_p);


    for (int i = 0; i < n - k + 1; ++i) {
        set_p.erase(a[i]);
        set_p.insert(a[i + k]);

        range = min(range, get_range(set_p));
    }

    cout << range << endl;
    
    return 0;
}