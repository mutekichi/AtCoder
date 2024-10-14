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
void output_vector(vector<T> v, bool debug) {
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

struct person {
    int team;
    int strength;
};

int main() {

    int n;
    cin >> n;
    
    vector<person> v(n);

    int sum = 0;

    vector<int> team_strength(n, 0);

    for (int i = 0; i < n; ++i) {
        int team, strength;
        cin >> team >> strength;
        v[i] = {team, strength};

        team_strength[team - 1] += strength;
        sum += strength;
    }

    if (sum % 3 != 0) {
        cout << -1 << endl;
        return 0;
    }

    vector<vector<vector<int>>> dp(
        n + 1, vector<vector<int>>(
            sum + 1, vector<int>(sum + 1, INT_MAX)
        )
    );

    // dp[i][j][k] = min movement counts for considering 0 ~ i th person, team 0 has j strength, team 1 has k strength

    dp[0][team_strength[0]][team_strength[1]] = 0;

    for (int i = 0; i < n; ++i) {
        int strength = v[i].strength;
        if (v[i].team == 1) {
            for (int j = 0; j <= sum; ++j) {
                for (int k = 0; k <= sum; ++k) {
                    if (dp[i][j][k] == INT_MAX) {
                        continue;
                    }
                    dp[i + 1][j][k] = min(dp[i + 1][j][k], dp[i][j][k]);
                    if (j >= strength) {
                        dp[i + 1][j - strength][k] = min(
                            dp[i + 1][j - strength][k], dp[i][j][k] + 1
                        );
                        dp[i + 1][j - strength][k + strength] = min(
                            dp[i + 1][j - strength][k + strength], dp[i][j][k] + 1
                        );
                    }
                }
            }
        } else if (v[i].team == 2) {
            for (int j = 0; j <= sum; ++j) {
                for (int k = 0; k <= sum; ++k) {
                    if (dp[i][j][k] == INT_MAX) {
                        continue;
                    }
                    dp[i + 1][j][k] = min(dp[i + 1][j][k], dp[i][j][k]);
                    if (k >= strength) {
                        dp[i + 1][j][k - strength] = min(
                            dp[i + 1][j][k - strength], dp[i][j][k] + 1
                        );
                        dp[i + 1][j + strength][k - strength] = min(
                            dp[i + 1][j + strength][k - strength], dp[i][j][k] + 1
                        );
                    }
                }
            }
        } else {
            for (int j = 0; j <= sum; ++j) {
                for (int k = 0; k <= sum; ++k) {
                    if (dp[i][j][k] == INT_MAX) {
                        continue;
                    }
                    dp[i + 1][j][k] = min(dp[i + 1][j][k], dp[i][j][k]);
                    dp[i + 1][j + strength][k] = min(
                        dp[i + 1][j + strength][k], dp[i][j][k] + 1
                    );
                    dp[i + 1][j][k + strength] = min(
                        dp[i + 1][j][k + strength], dp[i][j][k] + 1
                    );
                }
            }
        }
    }

    cout << (dp[n][sum / 3][sum / 3] == INT_MAX ? -1 : dp[n][sum / 3][sum / 3]) << endl;

    return 0;
}