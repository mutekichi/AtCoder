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

/**
 * @brief Get next positions of each character in the string.
 * 
 * @param s The string.
 * @param s_length The length of the string.
 * @param alphabet_size The size of the alphabet.
 * @return vector<vector<int>> The next positions of each character in the string. np[i][j] is the next position of character j in the string s starting from position i.
 * 
 
*/
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
}