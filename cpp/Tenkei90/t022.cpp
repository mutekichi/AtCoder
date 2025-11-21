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

long long gcd(long long a, long long b) {
    if (a > b) swap(a, b);
    if (b % a == 0) return a;
    else return gcd(b % a, a);
}

int main() {

    long long a, b, c;
    cin >> a >> b >> c;

    long long gcd_abc = gcd(gcd(a, b), c);

    cout << (a / gcd_abc - 1) + (b / gcd_abc - 1) + (c / gcd_abc - 1);

    return 0;
}