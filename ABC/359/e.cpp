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

debug_cout dbgcout(true);


std::vector<int> findPreviousLargerIndices(const std::vector<long long>& arr) {
    int n = arr.size();
    std::vector<int> result(n, -1); // 結果のベクターを初期化
    std::stack<long long> s; // インデックスを保持するスタック

    // 配列を前から順に走査
    for (int i = 0; i < n; ++i) {
        // スタックのトップが現在の要素よりも小さい場合、スタックからポップする
        while (!s.empty() && arr[s.top()] <= arr[i]) {
            s.pop();
        }
        // スタックが空でない場合、スタックのトップが直前のより大きい値のインデックス
        if (!s.empty()) {
            result[i] = s.top();
        }
        // 現在のインデックスをスタックにプッシュ
        s.push(i);
    }

    return result;
}

int main() {

    int n;
    cin >> n;

    vector<long long> heights(n);

    for (int i = 0; i < n; i++) cin >> heights[i];

    vector<int> max_index_until = findPreviousLargerIndices(heights);

    long long current_water = 0ll;

    vector<long long> ans(n, 0ll);

    for (int i = 0; i < n; ++i) {
        if (max_index_until[i] == -1) {
            ans[i] = heights[i] * (i + 1ll);
        } else {
            ans[i] = heights[i] * (i - max_index_until[i]) + ans[max_index_until[i]];
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i] + 1ll << endl;
    }


    return 0;
}