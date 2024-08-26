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

debug_cout dbgcout(true);

template<typename T>
void print_vector(vector<T> v, bool debug) {
    for (int i = 0; i < v.size(); i++) {
        if (debug) {
            dbgcout << v[i] << " ";
        }
        else {
            cout << v[i] << " ";
        }
    }
    if (debug) {
        dbgcout << endl;
    }
    else {
        cout << endl;
    }
}

const int MAX = 100050;
vector<int> calculateExponentSum() {
    std::vector<int> exponentSum(MAX, 0);
    
    for (int i = 2; i < MAX; ++i) {
        if (exponentSum[i] == 0) { // iが素数の場合
            for (int j = i; j < MAX; j += i) {
                int num = j;
                int count = 0;
                while (num % i == 0) {
                    num /= i;
                    ++count;
                }
                exponentSum[j] += count; // 素因数iの指数を加算
            }
        }
    }
    
    return exponentSum;
}
int main() {

    int n;
    cin >> n;

    vector<int> grundies = calculateExponentSum();

    int grundy = 0;
    
    for (int i = 0; i < n; ++i) {
        int n;
        cin >> n;
        grundy ^= grundies[n];
    }

    if (grundy == 0) {
        cout << "Bruno" << endl;
    }
    else {
        cout << "Anna" << endl;
    }

    return 0;
}
