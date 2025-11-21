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
    int n;

    cin >> n;

    vector<long long> class1_score_sums(n, 0);
    vector<long long> class2_score_sums(n, 0);

    int class_num;
    long long score;

    for (int i = 1; i < n + 1; ++i) {
        cin >> class_num >> score;

        if (class_num == 1) {
            class1_score_sums[i] = class1_score_sums[i - 1] + score;
            class2_score_sums[i] = class2_score_sums[i - 1];
        } else {
            class1_score_sums[i] = class1_score_sums[i - 1];
            class2_score_sums[i] = class2_score_sums[i - 1] + score;
        }
    }
    
    int q;
    cin >> q;

    int l, r;

    for (int i = 0; i < q; ++i) {
        cin >> l >> r;

        cout << class1_score_sums[r] - class1_score_sums[l - 1] << " " << class2_score_sums[r] - class2_score_sums[l - 1] << endl;
    }

    return 0;
}