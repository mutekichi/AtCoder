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

unsigned long long sanjoukon_floor(unsigned long long n) {
    for (unsigned long long i = 0; i < 10000000; ++i) {
        if (i * i * i > n) {
            return i - 1;
        }
    }
    return 0;
};

unsigned long long ketasuu(unsigned long long n) {
    unsigned long long count = 0;

    while (n >= 1) {
        n /= 10;
        count++;
    }
    return count;
};

unsigned long long bekijou(unsigned long long n, unsigned long long k) {
    if (k == 0) return 1;
    return bekijou(n, k - 1) * n;
}

unsigned long long n_ketame(unsigned long long n, unsigned long long keta) {
    return (n / bekijou(10, ketasuu(n) - keta)) % 10;
};

bool check_kaibun(unsigned long long n) {

    unsigned long long k = ketasuu(n);

    for (unsigned long long i = 1; i < k/2 + 1; ++i) {
        // cout << n_ketame(n, i) << " " << n_ketame(n, k - i + 1) << endl;
        if (n_ketame(n, i) != n_ketame(n, k - i + 1)) {
            return false;
        }
    }

    return true;
}

int main() {

    unsigned long long n;

    cin >> n;

    unsigned long long max_value = sanjoukon_floor(n);

    // cout << check_kaibun(1334996994331) << endl;

    for (unsigned long long i = max_value; i >= 1; --i) {
        unsigned long long target = i * i * i;
        if (check_kaibun(target)) {
            cout << target << endl;
            return 0;
        }
    }
    
    return 0;
}