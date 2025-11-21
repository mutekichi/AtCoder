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

bool check_is_valid_parentheses(int parentheses, int n) {
    int score = 0;

    for (int i = n - 1; i >= 0; --i) {
        if (parentheses & (1 << i)) ++score;
        else --score;
        if (score < 0) return false;
    }

    if (score == 0) return true;
    else return false;
}

void output_as_parentheses(int parentheses, int n) {
    for (int bit = n - 1; bit >= 0; --bit) {
        if (parentheses & (1 << bit)) cout << "(";
        else cout << ")";
    }
    cout << endl;
}

int main() {

    int n;
    cin >> n;

    if (n % 2 == 1) return 0;
    
    for (int bits = (1 << n) - 1; bits >= 0; --bits) {
        if (check_is_valid_parentheses(bits, n)) {
            output_as_parentheses(bits, n);
        }
    }
    
    return 0;
}