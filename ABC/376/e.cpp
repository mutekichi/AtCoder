#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <tuple>
#include <set>

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
void output_vector(vector<T> v, bool debug) {
    for (const auto& elem : v) {
        if (debug) {
            dbgcout << elem << " ";
        } else {
            cout << elem << " ";
        }
    }
    if (debug) {
        dbgcout << endl;
    } else {
        cout << endl;
    }
}

int main() {
    long long t;
    cin >> t;

    for (long long _i = 0; _i < t; ++_i) {
        long long n, k;
        cin >> n >> k;
        
        vector<pair<long long, long long>> a(n); // first value, index
        vector<pair<long long, long long>> b(n); // second value, index

        for (long long i = 0; i < n; ++i) {
            cin >> a[i].first;
            a[i].second = i;
        }
        for (long long i = 0; i < n; ++i) {
            cin >> b[i].first;
            b[i].second = i;
        }

        sort(a.begin(), a.end(), greater<pair<long long, long long>>());
        sort(b.begin(), b.end());

        vector<bool> used(n, false);

        vector<long long> index_to_b_index(n);

        for (long long i = 0; i < n; ++i) {
            index_to_b_index[b[i].second] = i;
        }

        long long sum = 0;
        for (long long i = 0; i < k; ++i) {
            sum += b[i].first;
            used[b[i].second] = true;
        }

        long long ans = LLONG_MAX;

        for (long long i = 0; i < n - k + 1; ++i) {
            ans = min(ans, sum * a[i].first);
            if (i < n - k && used[a[i].second]) {
                sum -= b[index_to_b_index[a[i].second]].first;
                sum += b[k + i].first;
            } else {
                used[a[i].second] = true;
            }
        }

        cout << ans << endl;
    }

    return 0;
}