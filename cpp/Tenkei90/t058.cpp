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

int sum_digits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

pair<int, int> calc_next_loop(int n) {
    int step = 0;
    while(n < 100000) {
        n = n + sum_digits(n);
        step++;
    }
    return make_pair(n % 100000, step);
}

int main() {

    int n;
    cin >> n;
    int k;
    cin >> k;


    
    return 0;
}