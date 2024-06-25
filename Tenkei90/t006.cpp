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

int get_int_from_char(char c) {
    return c - 'a';
}

char get_char_from_int(int i) {
    return i + 'a';
}

vector<vector<int>> get_next_positions(string &s, int s_length, int alphabet_size) {
    vector<vector<int>> next_positions(s_length, vector<int>(alphabet_size, s_length));

    for (int i = s_length - 1; i >= 0; --i) {
        for (int j = 0; j < alphabet_size; ++j) {
            if (get_int_from_char(s[i]) == j) {
                next_positions[i][j] = i;
            } else {
                next_positions[i][j] = i == s_length - 1 ? s_length : next_positions[i + 1][j];
            }
        }
    }

    return next_positions;
}

const int ALPHABET_SIZE = 26;

int main() {

    int n, k;

    cin >> n >> k;

    string s;

    cin >> s;



    vector<vector<int>> next_positions = get_next_positions(s, n, ALPHABET_SIZE);

    int current_result_length = 0;

    int current_position = 0;

    while (current_result_length < k) {
        int alphabet_index = 0;
        while (alphabet_index < ALPHABET_SIZE) {
            if (next_positions[current_position][alphabet_index] + (k - current_result_length) <= n) {
                cout << get_char_from_int(alphabet_index);
                ++current_result_length;
                current_position = next_positions[current_position][alphabet_index] + 1;
                break;
            } else {
                ++alphabet_index;
            }
        }
    }
    
    cout << endl;


    return 0;
}