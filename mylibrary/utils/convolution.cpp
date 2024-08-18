#include <iostream>
#include <stdio.h>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

template <typename T>
void fft(vector<complex<T>> &a, bool invert) {
    int n = a.size();
    if (n == 1) {
        return;
    }
    vector<complex<T>> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; ++i) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    fft(a0, invert);
    fft(a1, invert);
    double ang = 2 * M_PI / n * (invert ? -1 : 1);
    complex<T> w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

/**
 * @brief Convolution
 * 
 * @tparam T 
 * @param a The first vector
 * @param b The second vector
 * @return vector<T> The convolution of a and b
 * 
 * @note The time complexity is O(n log n). conv[i] = sum(a[j] * b[i - j]) for all j
 */
template <typename T>
vector<T> convolution(const vector<T> &a, const vector<T> &b) {
    int n = a.size();
    int m = b.size();
    int sz = 1;
    while (sz < n + m - 1) {
        sz *= 2;
    }
    vector<complex<double>> fa(sz), fb(sz);
    for (int i = 0; i < n; ++i) {
        fa[i] = complex<double>(a[i], 0);
    }
    for (int i = 0; i < m; ++i) {
        fb[i] = complex<double>(b[i], 0);
    }
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < sz; ++i) {
        fa[i] *= fb[i];
    }
    fft(fa, true);
    vector<T> res(n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) {
        res[i] = (T)(fa[i].real() + 0.5);
    }
    return res;
}

int main() {
    vector<int> a = {1, 2, 3, 4, 5};
    vector<int> b = {1, 2, 3, 4};
    vector<int> c = convolution(a, b);
    
    // naive convolution
    vector<int> d(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            d[i + j] += a[i] * b[j];
        }
    }

    cout << "convolution result" << endl;
    cout << "---" << endl;
    cout << "naive: ";
    for (int i = 0; i < d.size(); ++i) {
        cout << d[i] << " ";
    }
    cout << endl;

    cout << "fft  : ";
    for (int i = 0; i < c.size(); ++i) {
        cout << c[i] << " ";
    }
}