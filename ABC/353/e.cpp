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

bool is_unchosen(long long state, int n) {
    return (state & (1 << n)) == 0;
}

bool is_state_winning(long long state, int n) {
    for (int i = 0; i < n; ++i) {
        if (is_unchosen(state, i)) {
            if ()
        }
    }
}

int main() {

    int n;

    cin >> n;

    unsigned long long a, b;

    vector<int> omote(n), ura(n);
    vector<vector<int>> graph(n);

    for (int i = 0; i < n; ++i) {
        cin >> omote[i] >> ura[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (omote[i] == omote[j] || ura[i] == ura[j]) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }
    
    



    
    return 0;
}