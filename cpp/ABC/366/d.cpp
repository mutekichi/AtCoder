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

debug_cout dbgcout(true);
class CumulativeSum3D {
private:
    vector<vector<vector<long long>>> sum;

public:
    CumulativeSum3D(const vector<vector<vector<long long>>>& A) {
        int X = A.size();
        int Y = A[0].size();
        int Z = A[0][0].size();
        
        sum = vector<vector<vector<long long>>>(X + 1, vector<vector<long long>>(Y + 1, vector<long long>(Z + 1, 0)));

        for (int x = 1; x <= X; ++x) {
            for (int y = 1; y <= Y; ++y) {
                for (int z = 1; z <= Z; ++z) {
                    sum[x][y][z] = A[x-1][y-1][z-1]
                                   + sum[x-1][y][z]
                                   + sum[x][y-1][z]
                                   + sum[x][y][z-1]
                                   - sum[x-1][y-1][z]
                                   - sum[x-1][y][z-1]
                                   - sum[x][y-1][z-1]
                                   + sum[x-1][y-1][z-1];
                }
            }
        }
    }

    long long getSum(int x1, int y1, int z1, int x2, int y2, int z2) {
        return sum[x2+1][y2+1][z2+1]
               - sum[x1][y2+1][z2+1]
               - sum[x2+1][y1][z2+1]
               - sum[x2+1][y2+1][z1]
               + sum[x1][y1][z2+1]
               + sum[x1][y2+1][z1]
               + sum[x2+1][y1][z1]
               - sum[x1][y1][z1];
    }
};

int main() {
    int n;
    cin >> n;

    vector<vector<vector<long long>>> A(n, vector<vector<long long>>(n, vector<long long>(n, 0)));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                cin >> A[i][j][k];
            }
        }
    }

    CumulativeSum3D cs3d(A);

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int x1, x2, y1, y2, z1, z2;
        cin >> x1 >> x2 >> y1 >> y2 >> z1 >> z2;
        x1--; x2--; y1--; y2--; z1--; z2--;

        cout << cs3d.getSum(x1, y1, z1, x2, y2, z2) << endl;
    }

    return 0;
}
