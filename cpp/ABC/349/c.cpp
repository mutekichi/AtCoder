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

    string s, capitals;

    cin >> s >> capitals;

    if (capitals[2] == 'X') {
        int s_index = 0;
        int t_index = 0;
        while (s_index < s.size() && t_index < 2) {
            if (s[s_index] == capitals[t_index] + 32) {
                ++s_index;
                ++t_index;
            }else {
                ++s_index;
            }
        }
        if (t_index == 2) {
            cout << "Yes" << endl;
        } else cout << "No" << endl;
    } else {
        int s_index = 0;
        int t_index = 0;
        while (s_index < s.size() && t_index < 3) {
            if (s[s_index] == capitals[t_index] + 32) {
                ++s_index;
                ++t_index;
            }else {
                ++s_index;
            }
        }
        if (t_index == 3) {
            cout << "Yes" << endl;
        } else cout << "No" << endl;
    }

    
    
    return 0;
}