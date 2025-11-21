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


/**
 * @brief Coordinate Compression
 * 
 * @param coordinates <vector<long long> &>: coordinates to be compressed
 */
class CoordinateCompression {
public:
    CoordinateCompression(vector<long long> &coordinates) {
        sort(coordinates.begin(), coordinates.end());
        coordinates.erase(unique(coordinates.begin(), coordinates.end()), coordinates.end());
        compressed.resize(coordinates.size());
        for (int i = 0; i < coordinates.size(); ++i) {
            compressed[i] = coordinates[i];
            decompressed[coordinates[i]] = i;
        }
    }

    long long compress(long long coordinate) {
        return decompressed[coordinate];
    }

    long long decompress(long long coordinate) {
        return compressed[coordinate];
    }

private:
    vector<long long> compressed;
    map<long long, long long> decompressed;

};

int main() {

    vector<long long> coordinates = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    CoordinateCompression cc(coordinates);

    for (int i = 0; i < coordinates.size(); ++i) {
        cout << cc.compress(coordinates[i]) << " ";
    }
    
    return 0;


}