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

void rotate_point_90(int &x_after, int &y_after, int x, int y, int n) {
    x_after = y;
    y_after = n - x - 1;
}

void rotate_point_180(int &x_after, int &y_after, int x, int y, int n) {
    x_after = n - x - 1;
    y_after = n - y - 1;
}

void rotate_point_270(int &x_after, int &y_after, int x, int y, int n) {
    x_after = n - y - 1;
    y_after = x;
}

void rotate(int &x_after, int &y_after, int x, int y, int n, int k) {
    if (k == 0) {
        x_after = x;
        y_after = y;
    }
    else if (k == 1) {
        rotate_point_90(x_after, y_after, x, y, n);
    }
    else if (k == 2) {
        rotate_point_180(x_after, y_after, x, y, n);
    }
    else if (k == 3) {
        rotate_point_270(x_after, y_after, x, y, n);
    }
}

void print_board(vector<vector<char>> &v, int n) {
    for (int i = 0; i <n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << v[i][j];
        }
        cout << endl;
    }
}

void rotateMatrixLayer(const vector<vector<char>>& orig, vector<vector<char>>& ans, int i, int k) {
    int N = orig.size();
    k = k % 4;  // k を 0-3 の範囲に正規化

    // i番目の正方形の回転
    for (int j = i; j < N - i - 1; j++) {
        int x1 = i, y1 = j;
        int x2 = j, y2 = N - 1 - i;
        int x3 = N - 1 - i, y3 = N - 1 - j;
        int x4 = N - 1 - j, y4 = i;

        switch (k) {
            case 0:  // 0度回転（変更なし）
                ans[x1][y1] = orig[x1][y1];
                ans[x2][y2] = orig[x2][y2];
                ans[x3][y3] = orig[x3][y3];
                ans[x4][y4] = orig[x4][y4];
                break;
            case 1:  // 90度回転
                ans[x2][y2] = orig[x1][y1];
                ans[x3][y3] = orig[x2][y2];
                ans[x4][y4] = orig[x3][y3];
                ans[x1][y1] = orig[x4][y4];
                break;
            case 2:  // 180度回転
                ans[x3][y3] = orig[x1][y1];
                ans[x4][y4] = orig[x2][y2];
                ans[x1][y1] = orig[x3][y3];
                ans[x2][y2] = orig[x4][y4];
                break;
            case 3:  // 270度回転
                ans[x4][y4] = orig[x1][y1];
                ans[x1][y1] = orig[x2][y2];
                ans[x2][y2] = orig[x3][y3];
                ans[x3][y3] = orig[x4][y4];
                break;
        }
    }
}

int main() {

    int n;
    cin >> n;
    vector<vector<char>> v(n, vector<char>(n));
    vector<vector<char>> ans(n, vector<char>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ans[i][j] = 'x';
        }
    }

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < n; ++j) {
            v[i][j] = s[j];
        }
    }

    for (int i = 0; i < n / 2; ++i) {
        rotateMatrixLayer(v, ans, i, (i + 1) % 4);
    }

    print_board(ans, n);

    return 0;
}
