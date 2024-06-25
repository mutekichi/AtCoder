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

    long long sum_length = 0;
    long long max_head = 0;

    long long a, b;

    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        sum_length += a;
        max_head = max(max_head, b - a);
    }

    cout << sum_length + max_head << endl;
    
    return 0;
}