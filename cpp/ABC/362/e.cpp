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
#include <assert.h>
#include <iomanip>

using namespace std;

class debug_cout {
public:
    debug_cout(bool debug) : debug(debug) {}

    template<typename T>
    debug_cout& operator<<(const T& value) {
        if (debug) {
            cout << value;
        }
        return *this;
    }

    debug_cout& operator<<(std::ostream& (*manip)(std::ostream&)) {
        if (debug) {
            manip(std::cout);
        }
        return *this;
    }

private:
    bool debug;
};

template<typename T>
void print_vector(vector<T> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

debug_cout dbgcout(true);

// find the longest arithmetic progression with designated indices as the first and second elements
// note: numbers__with_count is sorted in ascending order
vector<int> search_arithmetic_progression(
    vector<pair<long long, int>> numbers_with_count,
    int first_index,
    int second_index
) {
    long long first_num = numbers_with_count[first_index].first;
    long long second_num = numbers_with_count[second_index].first;
    int d = second_num - first_num;

    vector<int> indices;
    indices.push_back(first_index);
    indices.push_back(second_index);

    long long current_num = second_num;

    while(true) {
        long long next_num = current_num + d;
        
        auto itr = lower_bound(numbers_with_count.begin(), numbers_with_count.end(), make_pair(next_num, 0));
        if (itr == numbers_with_count.end() || itr->first != next_num) {
            break;
        } else {
            indices.push_back(itr - numbers_with_count.begin());
            current_num = next_num;
        }
    }

    return indices;
}

int main() {

    int n;
    cin >> n;

    map<long long, int> numbers_with_count;

    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        numbers_with_count[a]++;
    }

    vector<long long> arithmetic_progression_count(n + 1, 0ll);

    vector<vector<long long>> combination_table(n + 1, vector<long long>(n + 1, 0ll));

    // calculate combination_table

    for (int i = 0; i <= n; ++i) {
        combination_table[i][0] = 1ll;
        combination_table[i][i] = 1ll;
    }

    long long mod = 998244353;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            combination_table[i][j] = combination_table[i - 1][j - 1] + combination_table[i - 1][j];
            combination_table[i][j] %= mod;
        }
    }

    // count arithmetic progression with tolerance = 0
    for (auto itr = numbers_with_count.begin(); itr != numbers_with_count.end(); ++itr) {
        long long a = itr->first;
        int count = itr->second;
        
        for (int i = 1; i <= count; ++i) {
            arithmetic_progression_count[i] += combination_table[count][i];
            arithmetic_progression_count[i] %= mod;
        }
    }
    
    // map to vector
    vector<pair<long long, int>> numbers_with_count_vector;
    for (auto itr = numbers_with_count.begin(); itr != numbers_with_count.end(); ++itr) {
        numbers_with_count_vector.push_back(make_pair(itr->first, itr->second));
    }

    for (int i = 0; i < numbers_with_count_vector.size(); i++) {
        for (int j = i + 1; j < numbers_with_count_vector.size(); j++) {
            
            vector<int> indices = search_arithmetic_progression(numbers_with_count_vector, i, j);
            
            for (int length = 2; length <= indices.size(); ++length) {
                long long num = 1ll;
            }
        }
    }

    return 0;
}
