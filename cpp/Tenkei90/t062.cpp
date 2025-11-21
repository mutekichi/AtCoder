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

    vector<vector<int>> graph(n);
    vector<bool> is_painted(n, false);
    queue<int> q;
    vector<int> ans;

    for (int i = 0; i < n; ++i) {
        int b, c;
        cin >> b >> c;
        b--; c--;
        if (i != b) graph[b].push_back(i);
        else q.push(i);
        if (i != c) graph[c].push_back(i);
        else q.push(i);
    }

    while(!q.empty()) {
        int v = q.front();
        q.pop();
        if (is_painted[v]) continue;
        else {
            is_painted[v] = true;
            for (auto u: graph[v]) {
                q.push(u);
            }
            ans.push_back(v);
        }
    }

    if (ans.size() == n) {
        reverse(ans.begin(), ans.end());
        for (auto a: ans) {
            cout << a + 1 << endl;
        }
    } else cout << -1 << endl;
    
    return 0;
}