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
#include <unordered_map>

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
    for (long long i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

debug_cout dbgcout(true);

long long countOddOnesSubarrays(const vector<bool>& arr) {
    long long n = arr.size();
    vector<long long> prefixXor(n);
    prefixXor[0] = arr[0];
    
    // 累積 XOR を計算する
    for (long long i = 1; i < n; ++i) {
        prefixXor[i] = prefixXor[i - 1] ^ arr[i];
    }
    
    // XOR 値の出現回数を記録するマップ
    unordered_map<long long, long long> xorCount;
    xorCount[0] = 1;  // 初期値 0 の XOR は1回出現したとみなす
    long long countOddSubarrays = 0;
    
    for (long long i = 0; i < n; ++i) {
        long long currentXor = prefixXor[i];
        
        // 累積 XOR が奇数のとき
        if (currentXor % 2 == 1) {
            countOddSubarrays += xorCount[0];
        } else {
            countOddSubarrays += xorCount[1];
        }
        
        // 現在の XOR の値をマップに追加
        xorCount[currentXor]++;
    }
    
    return countOddSubarrays;
}

int main() {

    long long ans = 0ll;
    long long n;
    cin >> n;

    vector<long long> a(n);

    for (long long i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    for (long long j = 0; j < 40; ++j) {
        vector<bool> bits(n);

        long long oneCount = 0ll;
        for (long long i = 0; i < n; ++i) {
            // i 番目の要素の j ビット目が立っているかどうか
            bits[i] = (a[i] >> j) & 1;
            if (bits[i]) {
                oneCount++;
            }
        }
        long long count = countOddOnesSubarrays(bits);

        //cout << "count: " << count - oneCount << endl;

        ans += (1ll << j) * (long long)(count - oneCount);
    }

    cout << ans << endl;

    return 0;
}
