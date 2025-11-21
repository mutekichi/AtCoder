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

    int k, n;
    cin >> n >> k;

    vector<long long> original(n), copy(n);
    for (int i = 0; i < n; ++i) {
        cin >> original[i];
        copy[i] = original[i];
    }

    sort(copy.begin(), copy.end());
    copy.erase(unique(copy.begin(), copy.end()), copy.end());

    map<long long, long long> compress_map;
    for (int i = 0; i < copy.size(); ++i) {
        compress_map[copy[i]] = i;
    }

    for (int i = 0; i < original.size(); ++i) {
        original[i] = compress_map[original[i]];
    }

    vector<long long> counts(copy.size(), 0);
    long long ans = 0;
    long long species = 0;
    long long left = 0;
    long long right = 0;

    while (true) {
        if (right == original.size()) break;
        if (species < k) {
            if (counts[original[right]] == 0) {
                ++species;
                ++counts[original[right]];
            } else {
                ++counts[original[right]];
            }
            ++right;
            ans = max(ans, right - left);
        } else {
            if (counts[original[right]] == 0) {
                --counts[original[left]];
                if (counts[original[left]] == 0) --species;
                ++left;
            } else {
                counts[original[right]]++;
                ++right;
                ans = max(ans, right - left);
            }
        } 
    }
    ans = max(ans, right - left);

    cout << ans << endl;

    return 0;
}