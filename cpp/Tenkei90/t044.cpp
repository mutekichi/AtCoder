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
    int q;
    cin >> q;

    int num;
    vector<int> num_seq(n);
    for (int i = 0; i < n; ++i) {
        cin >> num;
        num_seq[i] = num;
    }

    char query_type;
    int x, y;
    int head = 0;
    int tmp;

    for (int j = 0; j < q; ++j) {
        cin >> query_type;
        cin >> x >> y;
        x--; y--;
        if (query_type == '2') {
            head = head == 0 ? n - 1 : head - 1;
        } else if (query_type == '1') {
            int x_ring = (head + x) % n;
            int y_ring = (head + y) % n;
            swap(num_seq[x_ring], num_seq[y_ring]);
        } else if (query_type == '3') {
            int x_ring = (head + x) % n;
            cout << num_seq[x_ring] << endl;
        }
    }
    
    return 0;
}