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

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }


    vector<long long> longest_increasing_subsequence_lengths(n);
    vector<long long> longest_increasing_subsequence_lengths_from_end(n);

    vector<long long> sequence;
    for (int i = 0; i < n; ++i) {
        
        if (sequence.empty()) {
            sequence.push_back(a[i]);
            longest_increasing_subsequence_lengths[i] = 1;
        } else {
            if (sequence.back() < a[i]) {
                sequence.push_back(a[i]);
                longest_increasing_subsequence_lengths[i] = sequence.size();
            } else {
                auto it = lower_bound(sequence.begin(), sequence.end(), a[i]);
                *it = a[i];
                longest_increasing_subsequence_lengths[i] = it - sequence.begin() + 1;
            }
        }
    }

    vector<long long> sequence_from_end;
    for (int i = n - 1; i >= 0; --i) {
        
        if (sequence_from_end.empty()) {
            sequence_from_end.push_back(a[i]);
            longest_increasing_subsequence_lengths_from_end[i] = 1;
        } else {
            if (sequence_from_end.back() < a[i]) {
                sequence_from_end.push_back(a[i]);
                longest_increasing_subsequence_lengths_from_end[i] = sequence_from_end.size();
            } else {
                auto it = lower_bound(sequence_from_end.begin(), sequence_from_end.end(), a[i]);
                *it = a[i];
                longest_increasing_subsequence_lengths_from_end[i] = it - sequence_from_end.begin() + 1;
            }
        }
    }

    long long max_length = 0;
    for (int i = 0; i < n; ++i) {
        max_length = max(max_length, longest_increasing_subsequence_lengths[i] + longest_increasing_subsequence_lengths_from_end[i] - 1);
    }

    cout << max_length << endl;
    
    return 0;
}