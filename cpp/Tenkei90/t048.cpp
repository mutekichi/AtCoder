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

    int n, k;
    cin >> n >> k;

    vector<unsigned long long> scores(2 * n);

    unsigned long long a, b;

    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        scores[i] = b;
        scores[i + n] = a - b;
    }

    sort(scores.begin(), scores.end(), greater<unsigned long long>());

    unsigned long long result = accumulate(scores.begin(), scores.begin() + k, 0ull
        , [](unsigned long long acc, unsigned long long score) {
            return acc + score;
        });
    
    cout << result << endl;

    return 0;
}