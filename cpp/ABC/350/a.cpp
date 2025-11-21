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

    int n = stoi(s.substr(3, 3));

    if (0 < n && n < 350 && n != 316) {
        cout << "Yes" << endl;
    } else cout << "No" << endl;

    return 0;
}