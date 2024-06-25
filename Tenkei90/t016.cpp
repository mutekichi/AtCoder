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

    long long n;
    cin >> n;

    long long a, b, c;
    cin >> a >> b >> c;

    if (a == b) {
        for (int nums_sum = 0; nums_sum < 10000; ++nums_sum) {
            for (int nums_c = 0; nums_c <= nums_sum; ++nums_c) {
                if ((nums_sum - c * nums_c) % a == 0) {
                    if ((nums_sum - c * nums_c) / a == n) {
                        cout << nums_sum << endl;
                        return 0;
                    }
                }
            }
        }
    }

    if (a < b) {
        swap(a, b);
    }

    for (int i = 0; i < 10000; ++i) {
        for (int j = 0; j <= i; ++j) {
            if ((n - c * j - b * (i - j)) % (a - b) == 0) {
                int k_num  = (n - c * j - b * (i - j)) / (a - b);
                if (k_num >= 0 && k_num <= i - j) {
                    cout << i << endl;
                    return 0;
                }
            }
        }
    }
    
    return 0;
}