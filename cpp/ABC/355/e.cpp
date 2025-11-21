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
#include <iomanip>
#include <cstdlib>
#include <iomanip>

using namespace std;

int msb(long long x) {
    int res = 0;
    while (x > 0) {
        x >>= 1;
        res++;
    }
    return res - 1;
}

vector<pair<int, int>> segment_divide(long long l, long long r) {
    vector<pair<int, int>> res;
    int msb_l = msb(l);
    int msb_r = msb(r);
    if (msb_l == msb_r) {
        res.push_back(make_pair(msb_l, msb_r));
        return res;
    }
    res.push_back(make_pair(msb_l, msb_l));
    res.push_back(make_pair(msb_r, msb_r));
    for (int i = msb_l + 1; i < msb_r; i++) {
        res.push_back(make_pair(i, i));
    }
    return res;
}

int main() {
    
    vector<pair<int, int>> res = segment_divide(1, 10);

    for(auto p : res) {
        cout << p.first << " " << p.second << endl;
    }
    
    return 0;
}