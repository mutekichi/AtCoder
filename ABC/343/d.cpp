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

    int n, t;

    cin >> n >> t;

    vector<long long> scores_by_person(n, 0);

    multiset<long long> scores_multiset;

    for (int i = 0; i < n; ++i) {
        scores_multiset.insert(0);
    }

    set<long long> scores_set;

    scores_set.insert(0);

    int a;
    long long b;

    for (int i = 0; i < t; ++i) {
        cin >> a >> b;
        a--;

        scores_multiset.erase(scores_multiset.find(scores_by_person[a]));
        if (scores_multiset.find(scores_by_person[a]) == scores_multiset.end()) {
            scores_set.erase(scores_by_person[a]);
        }

        scores_by_person[a] += b;

        scores_multiset.insert(scores_by_person[a]);
        scores_set.insert(scores_by_person[a]);

        cout << scores_set.size() << endl;
        
    }
    
    return 0;
}