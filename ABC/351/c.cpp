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

unsigned long long count_set_bits(unsigned long long num) {
    unsigned long long count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

unsigned long long LSB(unsigned long long num) {
    return num & -num;
}

int main() {
    long long n;
    cin >> n;

    
    
    return 0;
}