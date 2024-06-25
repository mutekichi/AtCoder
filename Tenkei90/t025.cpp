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

long long n, b;
long long cnt_search = 0;
int cnt = 0;

long long product_digit(long long int_x) {
    long long res = 1;
    while (int_x > 0) {
        res *= int_x % 10;
        int_x /= 10;
    }
    return res;
}

bool include_zero_digit(long long int_x) {
    if (product_digit(int_x) == 0) return true;
    return false;
}

bool check_cond(long long int_x) {
    if (int_x > n) return false; 

    long long target = product_digit(int_x) + b;
    string str_x = to_string(int_x);
    string str_target = to_string(target);
    sort(str_x.begin(), str_x.end());
    sort(str_target.begin(), str_target.end());
    return (str_x == str_target);

}

void dfs(string int_s) {
    if (int_s.size() == 11) {
        long long int_x = stoll(int_s);
        if (include_zero_digit(int_x)) {
            if (int_x == b) ++cnt;
        }
        if (check_cond(int_x)) {
            ++cnt;
        }
        return;
    }
    for (char c = int_s[int_s.size() - 1]; c <= '9'; ++c) {
        ++cnt_search;
        dfs(int_s + c);
    }
}

int main() {

    cin >> n >> b;

    for (char c = '0'; c <= '9'; ++c) {
        dfs(string(1, c));
    }

    cout << cnt << endl;
    // cout << cnt_search << endl;
    
    return 0;
}