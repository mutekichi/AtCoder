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

    vector<long long> schools(n);
    vector<long long> students(n);

    for (int i = 0; i < n; i++) {
        cin >> schools[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> students[i];
    }

    sort(schools.begin(), schools.end());
    sort(students.begin(), students.end());

    long long ans = 0;

    for (int i = 0; i < n; i++) {
        ans += abs(schools[i] - students[i]);
    }

    cout << ans << endl;

    return 0;
}