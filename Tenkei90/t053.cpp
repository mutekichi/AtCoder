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

int query(int q) {
    cout << "? " << q << endl;
    flush(cout);
    int ans;
    cin >> ans;
    return ans;
}

int point(int value) {
    cout << "! " << value << endl;
    flush(cout);
    return 0;

}

int main() {

    int t;
    cin >> t;

    for (int test_case = 0; test_case < t; ++test_case) {
        int n;
        cin >> n;

        if (n == 1) {
            int value = query(1);
            point(value);
        } else if (n == 2) {
            int left = query(1);
            int right = query(2);
            point(max(left, right));
        } else {
            int left = 1;
            int right = n;
            int left_value = query(left);
            int right_value = query(right);
            while(right - left > 2) {
                int left_middle = (left * 2 + right) / 3;
                int right_middle = (left + right * 2) / 3;
                int left_middle_value = query(left_middle);
                int right_middle_value = query(right_middle);
                
                if (left_middle_value < right_middle_value) {
                    left = left_middle;
                    left_value = left_middle_value;
                } else {
                    right = right_middle;
                    right_value = right_middle_value;
                }
            }
            if (right - left == 2) {
                int middle = (left + right) / 2;
                int middle_value = query(middle);
                point(max(left_value, max(middle_value, right_value)));
            } else {
                point(max(left_value, right_value));
            }
        }
    }

    return 0;
} 