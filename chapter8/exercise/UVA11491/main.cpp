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

const int maxn = 100000 + 10;
char buf[maxn];
int A[maxn];
int g[maxn][10];
int N, D;

void init() {
    Set(buf, 0);;
    Set(A, 0);
    Set(g, 0);
}

void initCal() {
    _rep(x, 0, 9) {
        int pos = N;
        _forDown(i, N - 1, 0) {
            if(A[i] == x) pos = i;
            g[i][x] = pos;
        }
    }
}

bool valid(int x, int L, int R, int E) {
    // can x valid in [L, R]
    return g[L][x] <= R && R - g[L][x] >= E;
}

int selectMax(int L, int R, int E, int& pos) {
    _forDown(x, 9, 0) {
        if(!valid(x, L, R, E)) continue;
        pos = g[L][x];
        return x;
    }
}

void solve(int E) {
    initCal();
    int L = 0;
    string ans;
    while (E--) {
        int pos;
        ans += selectMax(L, N - 1, E, pos) + '0';
        L = pos + 1;
    }
    cout << ans << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    while(scanf("%d%d", &N, &D) == 2 && N && D) {
        init();

        scanf("%s", buf);
        _for(i, 0, N) A[i] = buf[i] - '0';
        // input finished

        solve(N - D);
    }
}