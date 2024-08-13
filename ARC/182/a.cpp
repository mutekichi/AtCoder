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

debug_cout dbgcout(false);

int main() {

    int n, q;
    cin >> n >> q;

    set<tuple<int, int, int>> value_index_pivot_set;
    vector<pair<int, int>> value_pivot_list(q);

    for (int i = 0; i < q; ++i) {
        int p, v;
        cin >> p >> v;
        value_index_pivot_set.insert(make_tuple(v, i, p - 1));
        value_pivot_list[i] = make_pair(v, p - 1);
    }

    // print set 
    // for (auto it = value_index_pivot_set.begin(); it != value_index_pivot_set.end(); ++it) {
    //     cout << get<0>(*it) << " " << get<1>(*it) << " " << get<2>(*it) << endl;
    // }

    //last elem of set
    auto last_elem = value_index_pivot_set.rbegin();
    int index = get<1>(*last_elem);

    long long ans = 1ll;

    long long left_max = 0ll;
    long long right_max = 0ll;

    while(index >= 0) {
        if (index == value_index_pivot_set.size() - 1) {
            value_index_pivot_set.erase(
                make_tuple(get<0>(value_pivot_list[index]), index, get<1>(value_pivot_list[index]))
            );
            value_pivot_list.pop_back();
            ans *= 2ll;
            ans %= 998244353ll;
            if (index == 0) {
                break;
            }
        } else {
            pair<int, int> next_elem = value_pivot_list[index + 1];
            bool is_right;
            if (get<1>(next_elem) < get<1>(value_pivot_list[index])) {
                is_right = false;
                // erase left
                value_index_pivot_set.erase(
                    make_tuple(get<0>(value_pivot_list[index]), index, get<1>(value_pivot_list[index]))
                );
            } else if (get<1>(next_elem) > get<1>(value_pivot_list[index])) {
                is_right = true;
                // erase right
                value_index_pivot_set.erase(
                    make_tuple(get<0>(value_pivot_list[index]), index, get<1>(value_pivot_list[index]))
                );
            } else {
                cout << 0 << endl;
                return 0;
            }

            int current_value = next_elem.first;

            if (is_right) {
                int pop_count = 1;
                for (int i = index + 2; i < value_pivot_list.size(); ++i) {
                    int pivot = get<1>(value_pivot_list[i]);
                    int value = get<0>(value_pivot_list[i]);


                    if (value >= current_value && pivot > get<1>(value_pivot_list[index])) {
                        current_value = value;
                        value_index_pivot_set.erase(
                            make_tuple(value, i, pivot)
                        );
                        pop_count++;
                    } else {
                        cout << 0 << endl;
                        return 0;
                    }
                }
                while(pop_count > 0) {
                    value_pivot_list.pop_back();
                    pop_count--;
                }
            } else {
                int pop_count = 1;
                for (int i = index - 2; i >= 0; --i) {
                    int pivot = get<1>(value_pivot_list[i]);
                    int value = get<0>(value_pivot_list[i]);

                    if (value >= current_value && pivot < get<1>(value_pivot_list[index])) {
                        current_value = value;
                        value_index_pivot_set.erase(
                            make_tuple(value, i, pivot)
                        );
                        pop_count++;
                    } else {
                        cout << 0 << endl;
                        return 0;
                    }
                }
                while(pop_count > 0) {
                    value_pivot_list.pop_back();
                    pop_count--;
                }
            }
        }
        if (index == 0) {
            break;
        }
        index = get<1>(*value_index_pivot_set.rbegin());
    }

    cout << ans << endl;

    return 0;
}
