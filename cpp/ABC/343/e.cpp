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
#include <cstdlib>

using namespace std;

int main() {

    int v1, v2, v3;

    cin >> v1 >> v2 >> v3;

    if (v1 + v2 * 2 + v3 * 3 !=  7 * 7 * 7 * 3) {
        cout << "No" << endl;
        return 0;
    }

    int x[3];
    int y[3];
    int z[3];

    x[0] = 0;
    y[0] = 0;
    z[0] = 0;

    int x_v2[2];
    int y_v2[2];
    int z_v2[2];

    for (int x0 = 0; x0 <= 7; ++x0) {
        x[1] = x0;
        for (int y0 = 0; y0 <= 7; ++y0) {
            y[1] = y0;
            for (int z0 = 0; z0 <= 7; ++z0) {
                z[1] = z0;
                for (int x1 = -7; x1 <= 7; ++x1) {
                    x[2] = x1;
                    for (int y1 = -7; y1 <= 7; ++y1) {
                        y[2] = y1;
                        for (int z1 = -7; z1 <= 7; ++z1) {

                            z[2] = z1;
                            
                            int *x_left = max_element(x, x + 3);
                            int *x_right = min_element(x, x + 3);
                            int x_range = max(7 + *x_right - *x_left, 0);

                            int *y_left = max_element(y, y + 3);
                            int *y_right = min_element(y, y + 3);
                            int y_range = max(7 + *y_right - *y_left, 0);

                            int *z_left = max_element(z, z + 3);
                            int *z_right = min_element(z, z + 3);
                            int z_range = max(7 + *z_right - *z_left, 0);

                            int volume = x_range * y_range * z_range;

                            if (volume != v3) {
                                continue;
                            }

                            int v2_sum = 0;

                            for (int i = 0; i < 3; ++i) {
                                x_v2[0] = x[i];
                                y_v2[0] = y[i];
                                z_v2[0] = z[i];
                                x_v2[1] = x[(i + 1) % 3];
                                y_v2[1] = y[(i + 1) % 3];
                                z_v2[1] = z[(i + 1) % 3];

                                int *x_v2_left = max_element(x_v2, x_v2 + 2);
                                int *x_v2_right = min_element(x_v2, x_v2 + 2);
                                int x_v2_range = max(7 + *x_v2_right - *x_v2_left, 0);

                                int *y_v2_left = max_element(y_v2, y_v2 + 2);
                                int *y_v2_right = min_element(y_v2, y_v2 + 2);
                                int y_v2_range = max(7 + *y_v2_right - *y_v2_left, 0);

                                int *z_v2_left = max_element(z_v2, z_v2 + 2);
                                int *z_v2_right = min_element(z_v2, z_v2 + 2);
                                int z_v2_range = max(7 + *z_v2_right - *z_v2_left, 0);

                                v2_sum += x_v2_range * y_v2_range * z_v2_range;
                            }   

                            if (v2_sum != v2 + v3 * 3) {
                                continue;
                            } else {
                                cout << "Yes" << endl;
                                cout << x[0] << " " << y[0] << " " << z[0] << " ";
                                cout << x[1] << " " << y[1] << " " << z[1] << " ";
                                cout << x[2] << " " << y[2] << " " << z[2] << endl;

                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    
    return 0;
}