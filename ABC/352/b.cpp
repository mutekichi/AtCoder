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

    string s, t;

    cin >> s >> t;

    int t_idx = 0;

    for (int i = 0; i < s.size(); ++i) {
        char c = s[i];
        while(t[t_idx] != c) {
            t_idx++;
        }
        cout << ++t_idx;
        if (i != s.size() - 1) cout << " ";
    }

    cout << endl;
    
    return 0;
}