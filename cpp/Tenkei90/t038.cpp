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

long long gcm(long long a, long long b) {
    if (b == 0) {
        return a;
    } else {
        return gcm(b, a % b);
    }
}

int main() {

    long long a, b;
    cin >> a >> b;

    long long g = gcm(a, b);
    long long l = a / g * b;

    long long limit = 1000000000000000000;

    if (a / g > limit / b) {
        cout << "Large" << endl;
    } else {
        cout << l << endl;
    }
    
    return 0;
}