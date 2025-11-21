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

bool check_length_cuttable(unsigned long long target_length, vector<unsigned long long> a, int cut_nums) {
    int current_cut_nums = 0;
    unsigned long long current_cut_length = 0;

    for (int i = 0; i < a.size(); ++i) {
        if (current_cut_length + a[i] > target_length) {
            current_cut_nums += 1;
            // cout << current_cut_length << endl;
            current_cut_length = 0;
        } else current_cut_length += a[i];
    }
    // cout << "cut_nums" << current_cut_nums << endl;
    if (current_cut_nums <= cut_nums) return true;
    return false;
}


unsigned long long binary_search_yokan_length(
    unsigned long long left, unsigned long long right,
    vector<unsigned long long> a, int cut_nums
    ) {
    if (right - left == 1) return right;
    else {
        unsigned long long mid = (left + right) / 2;
        if (check_length_cuttable(mid, a, cut_nums)) {
            return binary_search_yokan_length(left, mid, a, cut_nums);
        } else {
            return binary_search_yokan_length(mid, right, a, cut_nums);
        }
    }
}


int main() {

    int n, k;
    unsigned long long l;

    cin >> n;
    cin >> l;
    cin >> k;

    vector<unsigned long long> a(n + 1);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    a[n] = l - a[n - 1];
    for (int i = n - 1; 0 < i; --i) {
        a[i] = a[i] - a[i - 1];
    }

    cout << binary_search_yokan_length(0, l + 1, a, k) << endl;

    
    return 0;
}