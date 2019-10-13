#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <bitset>
#include <assert.h>

using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;


#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _forS(i, l, r) for(set<int>::iterator i = (l); i != (r); i++)
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define _forDown(i, l, r) for(int i = (l); i >= r; i--)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;
#define debugArr(arr, x, y) _for(i, 0, x) { _for(j, 0, y) printf("%c", arr[i][j]); printf("\n"); }
#define _forPlus(i, l, d, r) for(int i = (l); i + d < (r); i++)

string S, T;
int diff[2][2];

void init() {
    Set(diff, 0);
}

int solve() {
    int q0 = 0, q1 = 0;
    int ans = 0;

    _for(i, 0, S.size()) if(S[i] != T[i]) {
        if(S[i] == '0') diff[0][1]++;
        if(S[i] == '1') diff[1][0]++;
        if(S[i] == '?' && T[i] == '0') q0++;
        if(S[i] == '?' && T[i] == '1') q1++;
    }

    int x = min(diff[0][1], diff[1][0]);
    ans = x + q0;
    diff[0][1] -= x;
    diff[1][0] -= x;

    if(diff[1][0] > q1) return -1;
    ans += diff[1][0] + diff[0][1] + q1;
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    cin >> kase;

    for(int t = 1; cin >> S >> T; t++) {
        init();
        int ans = solve();
        printf("Case %d: %d\n", t, ans);
    }
}