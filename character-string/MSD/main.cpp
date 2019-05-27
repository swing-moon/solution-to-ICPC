#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

const int R = 256;
const int M = 15;

int charAt(const string& str, int d) {
    if(d < str.size()) return str[d];
    else return -1;
}

void insertion_sort(vector<string>& svec, int lo, int hi, int d) {
    for(int i = lo+1; i <= hi; i++) {
        for(int j = i; j > lo; j--) if(charAt(svec[j], d) < charAt(svec[j-1], d))
            swap(svec[j], svec[j-1]);
    }
}

void MSD(vector<string>& svec, int lo, int hi, int d, vector<string>& aux) {
    if(hi <= lo) return;
    if(hi <= lo + M) {
        insertion_sort(svec, lo, hi, d); return;
    }

    int cnt[R+2]; memset(cnt, 0, sizeof(cnt));

    // 1 is for '/0', 0 we don't use
    for(int i = lo; i <= hi; i++)
        cnt[charAt(svec[i], d) + 2]++;
    for(int r = 0; r < R+1; r++)
        cnt[r+1] += cnt[r];
    for(int i = lo; i <= hi; i++)
        aux[cnt[1 + charAt(svec[i], d)]++] = svec[i];
    for(int i = lo; i <= hi; i++)
        svec[i] = aux[i-lo];

    // the first alpha is the same
    for(int r = 0; r < R; r++)
        MSD(svec, lo+cnt[r], lo+cnt[r+1]-1, d+1, aux);
}

// 如图所示，挡板会压缩，一直到lo == hi，退出

int main() {
    freopen("input.txt", "r", stdin);
    vector<string> svec;
    string str;
    while(cin >> str) svec.push_back(str);
    int n = svec.size();
    vector<string> aux(n);

    MSD(svec, 0, n-1, 0, aux);
    for(int i = 0; i < n; i++)
        cout << svec[i] << endl;
}