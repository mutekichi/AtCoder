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

    const unsigned long long BIG_NUM = 1000000000;

    unsigned long long a, b, c, d;
    cin >> a >> b >> c >> d;

    unsigned long long left_amari = (a + BIG_NUM) % 4;

    unsigned long long right_amari = (c + BIG_NUM) % 4;

    unsigned long long left_kiriyoshi;
    unsigned long long right_kiriyoshi;

    if (left_amari == 0) left_kiriyoshi = a;
    else left_kiriyoshi = a + (4 - left_amari);

    if (right_amari == 0) right_kiriyoshi = c;
    else right_kiriyoshi = c - right_amari;

    unsigned long long bottom_amari = (b + BIG_NUM) % 2;
    unsigned long long top_amari = (d + BIG_NUM) % 2;

    unsigned long long bottom_kiriyoshi;
    unsigned long long top_kiriyoshi;

    if (bottom_amari == 0) bottom_kiriyoshi = b;
    else bottom_kiriyoshi = b + (2 - bottom_amari);

    if (top_amari == 0) top_kiriyoshi = d;
    else top_kiriyoshi = d - top_amari;

    unsigned long long area = 0;

    unsigned long long area_width = (right_kiriyoshi - left_kiriyoshi) / 4;
    unsigned long long area_height = (top_kiriyoshi - bottom_kiriyoshi) / 2;
    
    unsigned long long area_center = 8 * area_width * area_height;

    unsigned long long area_left;
    unsigned long long area_right;
    unsigned long long area_bottom;
    unsigned long long area_top;

    if (left_amari == 0) area_left = 0;
    else if (left_amari == 3) area_left = area_height;
    else if (left_amari == 2) area_left = 2 * area_height;
    else area_left = 5 * area_height;

    if (right_amari == 0) area_right = 0;
    else if (right_amari == 1) area_right = 3 * area_height;
    else if (right_amari == 2) area_right = 6 * area_height;
    else area_right = 7 * area_height;

    if (bottom_amari == 0) area_bottom = 0;
    else area_bottom = 4 * area_width;

    if (top_amari == 0) area_top = 0;
    else area_top = 4 * area_width;

    unsigned long long area_bottomleft, area_bottomright, area_topleft, area_topright;

    if (bottom_amari == 0) {
        area_bottomleft = 0;
        area_bottomright = 0;
    } else {
        if (left_amari == 0) {
            area_bottomleft = 0;
        } else if (left_amari == 3) {
            area_bottomleft = 0;
        } else if (left_amari == 2) {
            area_bottomleft = 1;
        } else {
            area_bottomleft = 3;
        }
        if (right_amari == 0) {
            area_bottomright = 0;
        } else if (right_amari == 1) {
            area_bottomright = 1;
        } else if (right_amari == 2) {
            area_bottomright = 3;
        } else {
            area_bottomright = 4;
        }
    }

    if(top_amari == 0) {
        area_topleft = 0;
        area_topright = 0;
    } else {
        if (left_amari == 0) {
            area_topleft = 0;
        } else if (left_amari == 3) {
            area_topleft = 1;
        } else if (left_amari == 2) {
            area_topleft = 1;
        } else {
            area_topleft = 2;
        }
        if (right_amari == 0) {
            area_topright = 0;
        } else if (right_amari == 1) {
            area_topright = 2;
        } else if (right_amari == 2) {
            area_topright = 3;
        } else {
            area_topright = 3;
        }
    }

    // cout << "area_center: " << area_center << endl;
    // cout << "area_left: " << area_left << endl;
    // cout << "area_right: " << area_right << endl;
    // cout << "area_bottom: " << area_bottom << endl;
    // cout << "area_top: " << area_top << endl;
    // cout << "area_bottomleft: " << area_bottomleft << endl;
    // cout << "area_bottomright: " << area_bottomright << endl;
    // cout << "area_topleft: " << area_topleft << endl;
    // cout << "area_topright: " << area_topright << endl;


    area = area_center + area_left + area_right + area_bottom + area_top + area_bottomleft + area_bottomright + area_topleft + area_topright;
    
    cout << area << endl;

    return 0;
}