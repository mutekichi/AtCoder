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

    string s;
    cin >> s;

    vector<int> cnt(26, 0);
    vector<int> histgram(100, 0);

    for (int i = 0; i < s.size(); ++i) {
        cnt[s[i] - 'a']++;
    }

    for (int i = 0; i < cnt.size(); ++i) {
        histgram[cnt[i]]++;
    }

    for (int i = 1; i < histgram.size() + 1; ++i) {
        if (histgram[i] == 0 || histgram[i] == 2) continue;
        else {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;
    
    return 0;
}