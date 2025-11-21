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

    vector<string> names;

    string tmp_str;
    int tmp_score;

    int sum_score_mod = 0;

    for (int i = 0; i < n; ++i) {
        cin >> tmp_str >> tmp_score;
        names.push_back(tmp_str);
        sum_score_mod = (sum_score_mod + tmp_score) % n;
    }

    sort(names.begin(), names.end());

    cout << names[sum_score_mod] << endl;
    
    return 0;
}