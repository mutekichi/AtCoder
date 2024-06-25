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

    vector<tuple<unsigned long long, unsigned long long, int>> data;

    unsigned long long power, cost;

    for (int i = 0; i < n; ++i) {
        cin >> power >> cost;
        data.push_back(make_tuple(power, cost, i));
    }

    sort(data.begin(), data.end(), [](const tuple<unsigned long long, unsigned long long, int> &a, const tuple<unsigned long long, unsigned long long, int> &b) {
        if (get<0>(a) == get<0>(b)) {
            return get<1>(a) < get<1>(b);
        } else {
            return get<0>(a) > get<0>(b);
        }
    });

    // for (int i = 0; i < n; ++i) {
    //     cout << get<2>(data[i]) + 1 << endl;
    // }

    // return 0;

    vector<int> useful_cards;

    unsigned long long max_cost = ULLONG_MAX;

    for (int i = 0; i < n; ++i) {
        if (get<1>(data[i]) < max_cost) {
            useful_cards.push_back(get<2>(data[i]) + 1);
            max_cost = get<1>(data[i]);
        }
    }
    
    sort(useful_cards.begin(), useful_cards.end());

    cout << useful_cards.size() << endl;

    for (int i = 0; i < useful_cards.size(); ++i) {
        if (i != 0) cout << " ";
        cout << useful_cards[i];
    }
    cout << endl;

    return 0;
}