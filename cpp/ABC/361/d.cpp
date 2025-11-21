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
debug_cout dbgcout(false);

template<typename T>
void print_vector(vector<T> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

struct State {
    int state;
    int vacant;
};

int state_to_int(string state, int n) {
    int result = 0;
    for (int i = 0; i < n; ++i) {
        if (state[i] == 'B') {
            result += 1 << i;
        } else if (state[i] == 'W') {
            result += 0 << i;
        } else {
            assert(false);
        }
    }
    return result;
}

bool equal_states(State s1, State s2, int n) {
    return s1.state == s2.state && s1.vacant == s2.vacant;
}


string to_bitstring(int n, int num) {
    string result = "";
    for (int i = 0; i < n; ++i) {
        if (num & (1 << i)) {
            result += "B";
        } else {
            result += "W";
        }
    }
    return result;
}

State get_next_state(State current_state, int n, int pos_to_move) {
    int current_state_int = current_state.state;
    int current_vacant = current_state.vacant;

    assert(pos_to_move != current_vacant - 1);

    if (pos_to_move >= current_vacant) {
        int next_state_int = 0;
        for (int i = 0; i < current_vacant; ++i) {
            next_state_int += (current_state_int & (1 << i));
        }
        for (int i = current_vacant; i < pos_to_move; ++i) {
            next_state_int += ((current_state_int & (1 << i)) << 2);
        }
        for (int i = pos_to_move; i < pos_to_move + 2; ++i) {
            next_state_int += ((current_state_int & (1 << i)) >> (pos_to_move - current_vacant));
        }
        for (int i = pos_to_move + 2; i < n; ++i) {
            next_state_int += (current_state_int & (1 << i));
        }
        return {next_state_int, pos_to_move + 2};
    } else {
        int next_state_int = 0;
        for (int i = 0; i < pos_to_move; ++i) {
            next_state_int += (current_state_int & (1 << i));
        }
        for (int i = pos_to_move; i < pos_to_move + 2; ++i) {
            next_state_int += ((current_state_int & (1 << i)) << (current_vacant - pos_to_move - 2));
        }
        for (int i = pos_to_move + 2; i < current_vacant; ++i) {
            next_state_int += ((current_state_int & (1 << i)) >> 2);
        }
        for (int i = current_vacant; i < n; ++i) {
            next_state_int += (current_state_int & (1 << i));
        }
        return {next_state_int, pos_to_move};
    }
}

int main() {

    int n;
    cin >> n;

    string first_state_string;
    string target_state_string;

    cin >> first_state_string;
    cin >> target_state_string;


    // State ns = get_next_state({state_to_int("WBWB", 4), 2}, 4, 0);
    // dbgcout << to_bitstring(4, ns.state) << " " << ns.vacant << endl;
    // return 0;

    int state_nums = 1 << n;

    vector<vector<int>> dist(state_nums, vector<int>(n + 1, -1));
    queue<State> states_to_visit;

    states_to_visit.push({state_to_int(first_state_string, n), n});
    dist[state_to_int(first_state_string, n)][n] = 0;

    while (!states_to_visit.empty()) {
        State current_state = states_to_visit.front();
        states_to_visit.pop();

        int current_state_int = current_state.state;
        int vacant = current_state.vacant;
        int current_dist = dist[current_state_int][vacant];

        dbgcout << "now checking: " << to_bitstring(n, current_state_int) << " " << "vacant: " << vacant << " dist: " << current_dist << endl;

        if (equal_states(current_state, {state_to_int(target_state_string, n), n}, n)) {
            cout << current_dist << endl;
            return 0;
        }

        for (int i = 0; i < n - 1; ++i) {
            if (i == vacant - 1) continue;
            else {
                State next_state = get_next_state(current_state, n, i);
                dbgcout << "pushing: " << to_bitstring(n, next_state.state) << " " << "vacant: " << next_state.vacant << endl;
                int next_state_int = next_state.state;
                int next_vacant = next_state.vacant;
                if (dist[next_state_int][next_vacant] == -1) {
                    dist[next_state_int][next_vacant] = current_dist + 1;
                    states_to_visit.push(next_state);
                }
            }
        }
    }

    cout << -1 << endl;
    
    return 0;
}
