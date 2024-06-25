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

    string s;

    cin >> s;

    char ichimojime = s[0];
    char nimojime = s[1];

    if (ichimojime == nimojime) {
        int idx = 2;
        while (idx < s.size()) {
            if (ichimojime != s[idx]) {
                cout << idx + 1 << endl;
                return 0;
            }
            ++idx;
        }
        cout << -1 << endl;
    } else {
        if (ichimojime == s[2]) {
            cout << 2 << endl;
        } else {
            cout << 1 << endl;
        }
    }
    
    return 0;
}