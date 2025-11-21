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

int main() {

    int n, m, k;
    cin >> n >> m >> k;

    bool is_migiue_black = m % 2 == 0;
    bool is_migishita_black = n % 2 == 0;
    bool is_onaji = is_migiue_black == is_migishita_black;

    if (k % 2 == 0) {
        if (is_onaji) {
            cout << "No" << endl;
            return 0;
        } 
    } else {
        if (!is_onaji) {
            cout << "No" << endl;
            return 0;
        }
    }

    if (k < n) {
        cout << "No" << endl;
        return 0;
    }

    int k_n = k - n;
    int m_1 = m - 1;

    int tate_full_num = k_n / (2 * m_1);
    int amari = (k_n % m_1) / 2;

    cout << "Yes" << endl;
    
    for (int i = 0; i < 2 * m - 1; ++i) cout << "+";
    cout << "S";
    cout << "+";
    cout << endl;

    for (int i = 0; i < tate_full_num; ++i) {
        cout << "+";
        for (int j = 0; j < m; ++j) {
            cout << "o";
            if (j != m - 1) cout << ".";
        }
        cout << "+";
        cout << endl;

        cout << "+";
        cout << ".";
        for (int j = 0; j < m - 1; ++j) {
            cout << "+-";
        }
        cout << "+";
        cout << endl;
        
        cout << "+";
        for (int j = 0; j < m; ++j) {
            cout << "o";
            if (j != m - 1) cout << ".";
        }
        cout << "+";
        cout << endl;
    
        cout << "+";
        for (int j = 0; j < m - 1; ++j) {
            cout << "-+";
        }
        cout << ".";
        cout << "+";
        cout << endl;
    }



    if (amari > 0) {
        cout << "+";
        for (int i = 0; i < m - amari; ++i) {
            cout << "o";
            if (i != m - amari - 1) cout << ".";
            else cout << "|";
        }
        for (int i = 0; i < amari; ++i) {
            cout << "o";
            if (i != amari - 1) cout << ".";
        }
        cout << "+";
        cout << endl;

        for (int i = 0; i < m - amari + 1; ++i) {
            cout << "+.";
        }
        for (int i = 0; i < amari; ++i) {
            cout << "+-";
        }
        cout << "+";
        cout << endl;

        cout << "+";
        for (int i = 0; i < m - amari; ++i) {
            cout << "o";
            if (i != m - amari - 1) cout << ".";
            else cout << "|";
        }
        for (int i = 0; i < amari; ++i) {
            cout << "o";
            if (i != amari - 1) cout << ".";
        }
        cout << "+";
        cout << endl;
    }

    for (int i = 0; i < m - 1; ++i) {
        cout << "+-";
    }
    cout << "+.";
    cout << "+";
    cout << endl;


    

    return 0;
}