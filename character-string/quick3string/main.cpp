#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int charAt(const string& str, int d) {
    if(d < str.size()) return str[d];
    else return -1;
}

int exchange(vector<string>& a, int m, int n) {
    string tmp = a[m];
    a[m] = a[n];
    a[n] = tmp;

}

void quick3string(vector<string>& vec, int lo, int hi, int d) {
    if(hi <= lo) return;
    int lt = lo, gt = hi;
    int v = charAt(vec[lo], d);

    int i = lo+1;
    while(i <= gt) {
        // i and gt 不能同时i++ and gt--
        int tmp = charAt(vec[i], d);
        if(tmp < v) exchange(vec, lt++, i++);
        else if(tmp > v) exchange(vec, i, gt--);
        else i++;
    }

    quick3string(vec, lo, lt-1, d);
    if(v >= 0) quick3string(vec, lt, gt, d+1);
    quick3string(vec, gt+1, hi, d);

    // 双指针，小走大不走
    // 小的i值扔到lt前面去，lt往前走，i++
    // 大的呢？扔到gt后面，与此同时gt--, i不走
}

int main() {
    freopen("input.txt", "r", stdin);
    string str;
    vector<string> vec;
    while(cin >> str) vec.push_back(str);

    quick3string(vec, 0, vec.size()-1, 0);
    for(int i = 0; i < vec.size(); i++)
        cout << vec[i] << endl;
}