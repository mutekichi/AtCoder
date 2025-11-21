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

int minimum_excluded_number(const set<int> &numbers, int minimum) {
    if (numbers.find(minimum) == numbers.end()) return minimum;
    return minimum_excluded_number(numbers, minimum + 1);
}

int calc_grundy_numbers(vector<vector<int>> &grundy_numbers, int white_stones, int black_stones) {
    if (grundy_numbers[white_stones][black_stones] != -1) return grundy_numbers[white_stones][black_stones];

    if (white_stones == 0) {
        if (black_stones == 0 | black_stones == 1) {
            grundy_numbers[white_stones][black_stones] = 0;
            return 0;
        } else {
            set<int> next_grundy_numbers;
            for (int i = 1; i <= black_stones / 2; ++i) {
                next_grundy_numbers.insert(calc_grundy_numbers(grundy_numbers, white_stones, black_stones - i));
            }
            grundy_numbers[white_stones][black_stones] = minimum_excluded_number(next_grundy_numbers, 0);
            return grundy_numbers[white_stones][black_stones];
        }
    } else {
        if (black_stones == 0 | black_stones == 1) {
            if (calc_grundy_numbers(grundy_numbers, white_stones - 1, black_stones + white_stones) == 0) {
                grundy_numbers[white_stones][black_stones] = 1;
                return 1;
            } else {
                grundy_numbers[white_stones][black_stones] = 0;
                return 0;
            }
        } else {
            set<int> next_grundy_numbers;
            next_grundy_numbers.insert(calc_grundy_numbers(grundy_numbers, white_stones - 1, black_stones + white_stones));
            for (int i = 1; i <= black_stones / 2; ++i) {
                next_grundy_numbers.insert(calc_grundy_numbers(grundy_numbers, white_stones, black_stones - i));
            }
            grundy_numbers[white_stones][black_stones] = minimum_excluded_number(next_grundy_numbers, 0);
            return grundy_numbers[white_stones][black_stones];
        }
    }
}

int main() {

    int MAX_STONES = 50;

    int n;
    cin >> n;

    vector<int> white_stone_counts(n, 0);
    vector<int> black_stone_counts(n, 0);

    for (int i = 0; i < n; ++i) cin >> white_stone_counts[i];
    for (int i = 0; i < n; ++i) cin >> black_stone_counts[i];

    int max_black_stone_counts = MAX_STONES + (MAX_STONES + 1) * MAX_STONES / 2;

    vector<vector<int>> grundy_numbers(MAX_STONES + 1, vector<int>(max_black_stone_counts + 1, -1));

    int xor_sum = 0;

    for (int i = 0; i < n; ++i) {
        xor_sum ^= calc_grundy_numbers(grundy_numbers, white_stone_counts[i], black_stone_counts[i]);
    }

    if (xor_sum == 0) cout << "Second" << endl;
    else cout << "First" << endl;

    return 0;
}