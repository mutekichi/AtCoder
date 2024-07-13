#include <iostream>
#include <vector>
#include <map>

using namespace std;

void find_arithmetic_progression(
    const vector<long long> &a,
    const map<long long, vector<int>> &numbers_with_index,
    vector<int> &indices,
    vector<vector<int>> &found_arithmetic_progressions
) {
    long long diff = a[indices[1]] - a[indices[0]];
    long long next_num = a[indices[indices.size() - 1]] + diff;
    
    found_arithmetic_progressions.push_back(indices);

    // if not found
    if (numbers_with_index.find(next_num) == numbers_with_index.end()) {
        return;
    }

    vector<int> next_indices = numbers_with_index.at(next_num);

    for (int next_index : next_indices) {
        // if next_index is not ahead of the last index in indices
        if (next_index <= indices[indices.size() - 1]) {
            continue;
        }

        vector<int> new_indices = indices;
        new_indices.push_back(next_index);

        find_arithmetic_progression(a, numbers_with_index, new_indices, found_arithmetic_progressions);
    }
}

int main() {
    int n;
    cin >> n;

    vector<long long> a(n);
    map<long long, int> numbers_with_count;
    map<long long, vector<int>> numbers_with_index;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        numbers_with_count[a[i]]++;
        numbers_with_index[a[i]].push_back(i);
    }

    vector<vector<long long>> combination_table(n + 1, vector<long long>(n + 1, 0ll));
    vector<long long> arithmetic_progression_count(n + 1, 0ll);

    for (int i = 0; i <= n; ++i) {
        combination_table[i][0] = 1ll;
        combination_table[i][i] = 1ll;
    }

    long long mod = 998244353;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            combination_table[i][j] = (combination_table[i - 1][j - 1] + combination_table[i - 1][j]) % mod;
        }
    }

    for (auto itr = numbers_with_count.begin(); itr != numbers_with_count.end(); ++itr) {
        long long num = itr->first;
        int count = itr->second;

        for (int i = 1; i <= count; ++i) {
            arithmetic_progression_count[i] = (arithmetic_progression_count[i] + combination_table[count][i]) % mod;
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int first_num = a[i];
            int second_num = a[j];
            int diff = second_num - first_num;
            if (diff == 0) {
                continue;
            }

            vector<int> initial_indices = {i, j};
            vector<vector<int>> found_arithmetic_progressions;

            find_arithmetic_progression(a, numbers_with_index, initial_indices, found_arithmetic_progressions);


            for (const auto &progression : found_arithmetic_progressions) {
                int progression_size = progression.size();
                arithmetic_progression_count[progression_size] += 1ll;
                arithmetic_progression_count[progression_size] %= mod;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << arithmetic_progression_count[i];
        if (i != n) cout << " ";
        else cout << endl;
    }

    return 0;
}
