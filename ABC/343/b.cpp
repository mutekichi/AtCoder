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

    cin >> n;

    int a;

    for (int i = 0; i < n; ++i) {
        bool first = true;
        for (int j = 0; j < n; ++j) {
            cin >> a;
            if (a == 1) {
                if (!first) {
                    cout << " ";
                }
                cout << j + 1;
                first = false;
            }
        }
        if (!first) cout << endl;
    }
    
    return 0;
}