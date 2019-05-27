#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

const int R = 256;

vector<string> svec;
vector<string> aux;

void LSD(vector<string>& svec, int w) {
    int n = svec.size();
    aux.resize(n);

    for(int d = w-1; d >= 0; d--) {
        int cnt[R+1]; memset(cnt, 0, sizeof(cnt));

        for(int i = 0; i < n; i++)
            cnt[svec[i][d] + 1]++;
        for(int r = 0; r < R; r++)
            cnt[r+1] += cnt[r];
        for(int i = 0; i < n; i++)
            aux[cnt[svec[i][d]]++] = svec[i];
        for(int i = 0; i < n; i++)
            svec[i] = aux[i];
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    for(int i = 0; i < n; i++) {
        string str;
        cin >> str;
        svec.push_back(str);
    }

    LSD(svec, svec[0].length());
    for(int i = 0; i < svec.size(); i++)
        cout << svec[i] << endl;
}