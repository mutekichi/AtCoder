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
#include <bit>

using namespace std;

// return the least significant bit for example lsb(10) = 2, lsb(8) = 3
int lsb(unsigned long long x) {
    return __builtin_ctzll(x);
}

int main() {

    unsigned long long l, r;
    cin >> l >> r;
    unsigned long long l_init = l;

    unsigned long long l_list[200];

    int count = 0;

    while (l != r) {
        int i = 0;
        while (l % (1<<(i+1)) == 0 && l + (1<<(i+1)) <= r) {
            i++;
        }
        l_list[count] = 1<<i;
        count++;
        l += 1<<i;
    }

    cout << count << endl;

    l = l_init;
    for (int i = 0; i < count; ++i) {
        cout << l << " " << l + l_list[i] << endl;
        l += l_list[i];
    }

    
    return 0;
}