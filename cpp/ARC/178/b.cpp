// #include <iostream>
// #include <stdio.h>
// #include <cstdio>
// #include <string>
// #include <vector>
// #include <algorithm>
// #include <iterator>
// #include <functional>
// #include <numeric>
// #include <map>
// #include <set>
// #include <list>
// #include <queue>
// #include <stack>
// #include <deque>
// #include <bitset>
// #include <utility>
// #include <complex>
// #include <climits>
// #include <cfloat>
// #include <ctime>
// #include <iomanip>
// #include <cstdlib>
// #include <assert.h>
// #include <iomanip>

// using namespace std;

// class debug_cout {
// public:
//     debug_cout(bool debug) : debug(debug) {}

//     template<typename T>
//     debug_cout& operator<<(const T& value) {
//         if (debug) {
//             cout << value;
//         }
//         return *this;
//     }

//     debug_cout& operator<<(std::ostream& (*manip)(std::ostream&)) {
//         if (debug) {
//             manip(std::cout);
//         }
//         return *this;
//     }

// private:
//     bool debug;
// };

// debug_cout dbgcout(true);

// long long mod = 998244353;

// long long modpow(long long base, long long power) {
//     long long result = 1ll;
//     while (power > 0) {
//         if (power & 1) {
//             result = (result * base) % mod;
//         }
//         base = (base * base) % mod;
//         power >>= 1;
//     }
//     return result;
// }

// long long modadd(long long a, long long b) {
//     return (a + b) % mod;
// }

// long long modsub(long long a, long long b) {
//     return (a - b + mod) % mod;
// }

// long long modmul(long long a, long long b) {
//     return (a * b) % mod;
// }

// int main() {

//     int test_cases;
//     cin >> test_cases;

//     long long x1, x2, x3;
//     for (int i = 0; i < test_cases; ++i) {
//         cin >> x1 >> x2 >> x3;
//         if (x1 > x2) swap(x1, x2);

//         if (x2 == x3 - 1ll) {
//             if (x1 == x2) {

//             } else {
//                 if (x1 == 1ll) cout << 45 << endl;
//                 else {
//                     long long ten_x1_1 = modpow(10ll, x1 - 1ll);
//                     cout << modmul(45ll, modmul(ten_x1_1, modsub(modmul(11ll, ten_x1_1), 1ll))) << endl;
//                 }
//             }
//         } else if (x2 == x3) {
//             long long ten_x2 = modpow(10ll, x2);
//             long long ten_x1_1 = modpow(10ll, x1 - 1ll);

//             long long ans = modmul(810ll, modmul(ten_x2, ten_x1_1));

//             long long sub = modmul(45ll, modmul(ten_x1_1, modsub(modmul(11ll, ten_x1_1), 1ll)));

//             ans = modsub(ans, sub);
//             cout << ans << endl;
//         } else {
//             cout << 0 << endl;
//         }
//     }
// };