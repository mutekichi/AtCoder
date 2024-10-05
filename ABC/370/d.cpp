#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <utility>

using namespace std;

class IntervalSet {
private:
    std::set<std::pair<int, int>> intervals;

public:
    void addInterval(int start, int end) {
        auto it = intervals.lower_bound(make_pair(start, 0));
        
        if (it != intervals.begin() && std::prev(it)->second >= start) {
            --it;
            start = std::min(start, it->first);
            end = std::max(end, it->second);
            it = intervals.erase(it);
        }
        
        while (it != intervals.end() && it->first <= end) {
            end = std::max(end, it->second);
            it = intervals.erase(it);
        }
        
        intervals.insert(make_pair(start, end));
    }

    bool findIntervalContaining(int element, std::pair<int, int>& result) const {
        auto it = intervals.upper_bound(make_pair(element, std::numeric_limits<int>::max()));
        if (it != intervals.begin()) {
            --it;
            if (it->first <= element && element <= it->second) {
                result = *it;
                return true;
            }
        }
        return false;
    }

    bool isInInterval(int element) const {
        std::pair<int, int> dummy;
        return findIntervalContaining(element, dummy);
    }
};

class Grid {
private:
    int h, w;
    vector<IntervalSet> rowIntervals;
    vector<IntervalSet> colIntervals;
    long long destroyedWalls;

public:
    Grid(int height, int width) : h(height), w(width), destroyedWalls(0) {
        rowIntervals.resize(h);
        colIntervals.resize(w);
    }

    void placeBomb(int r, int c) {
        if (isWallDestroyed(r, c)) {
            // 既に壁がない場合、上下左右の最も近い壁を破壊
            destroyNearestWalls(r, c);
        } else {
            // 壁がある場合、その壁を破壊
            destroyWall(r, c);
        }
    }

    void destroyWall(int r, int c) {
        if (!isWallDestroyed(r, c)) {
            rowIntervals[r].addInterval(c, c + 1);
            colIntervals[c].addInterval(r, r + 1);
            destroyedWalls++;
        }
    }

    void destroyNearestWalls(int r, int c) {
        std::pair<int, int> interval;
        
        // 上方向
        if (colIntervals[c].findIntervalContaining(r, interval)) {
            if (interval.first > 0) destroyWall(interval.first - 1, c);
        }

        // 下方向
        if (colIntervals[c].findIntervalContaining(r, interval)) {
            if (interval.second < h) destroyWall(interval.second, c);
        }

        // 左方向
        if (rowIntervals[r].findIntervalContaining(c, interval)) {
            if (interval.first > 0) destroyWall(r, interval.first - 1);
        }

        // 右方向
        if (rowIntervals[r].findIntervalContaining(c, interval)) {
            if (interval.second < w) destroyWall(r, interval.second);
        }
    }

    bool isWallDestroyed(int r, int c) const {
        return rowIntervals[r].isInInterval(c) && colIntervals[c].isInInterval(r);
    }

    long long getDestroyedWallsCount() const {
        return destroyedWalls;
    }

    void printGrid() const {
        long long totalCells = static_cast<long long>(h) * w;
        long long remainingWalls = totalCells - destroyedWalls;
        
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                cout << (isWallDestroyed(i, j) ? '.' : '#');
            }
            cout << endl;
        }
    }
};

int main() {
    int h, w, q;
    cin >> h >> w >> q;

    Grid grid(h + 2, w + 2);

    for (int i = 0; i < q; ++i) {
        int r, c;
        cin >> r >> c;

        grid.placeBomb(r, c);
        grid.printGrid();
        cout << endl;
    }

    cout << h * w - grid.getDestroyedWallsCount() << endl;

    return 0;
}