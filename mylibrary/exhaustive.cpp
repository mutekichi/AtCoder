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

/**
 * @brief Exhaustive search for combinations
 * 
 * @param n the number of elements
 * @param r the number of elements to choose
 */
void exhaustive_combination(int n, int r, int bitstring = 0, int depth = 0, int level = 0) {
    if (depth > n) {
        return;
    }
    if (level == r) {
        for (int i = 0; i < n; ++i) {
            if (bitstring & (1 << i)) {
                // cout << i << " ";
            }
        }
        // cout << endl;
        return;
    }

    exhaustive_combination(n, r, bitstring | (1 << depth), depth + 1, level + 1);
    exhaustive_combination(n, r, bitstring, depth + 1, level);
}