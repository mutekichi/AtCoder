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

    set<string> usernames;
    string username;

    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            cin >> username;
            usernames.insert(username);
            cout << i + 1 << endl;
        } else {
            cin >> username;
            if (usernames.find(username) == usernames.end()) {
                usernames.insert(username);
                cout << i + 1 << endl;
            } else continue;
        }
    }
    
    return 0;
}