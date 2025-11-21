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

    int q;
    cin >> q;

    vector<long long> deck(200020);

    int top = 100010;
    int bottom = 100009;
    
    for (int i = 0; i < q; i++) {
        int t, x;
        cin >> t >> x;

        if (t == 1) deck[top++] = x;
        else if (t == 2) deck[bottom--] = x;
        else cout << deck[top - x] << endl;
    }
    
    return 0;
}