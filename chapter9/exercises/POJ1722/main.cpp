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
#define lowbit(i) (i & (-i))

const int BASE = 10000;
const int maxn = 20000 + 5;
const int maxl = 100 + 5;
int N, T;
int f[maxl][maxn];
int A[maxn];
int op[maxl];

void initdp() {
    Set(f, 0);
    Set(op, 0);
}

void dp() {
    f[1][BASE + A[1]] = 1;
    f[2][BASE + A[1] - A[2]] = -1;
    _rep(i, 3, N) _rep(j, 0,  BASE + BASE) {
        if(f[i - 1][j]) {
            f[i][j + A[i]] = 1;
            f[i][j - A[i]] = -1;
        }
    }
}

void out(int T) {
    int S = T + BASE;
    _forDown(i, N, 2) {
        op[i] = f[i][S];
        if(op[i] == 1) S -= A[i];
        if(op[i] == -1) S += A[i];
    }

    int cnt = 0;
    _rep(i, 2, N) {
        if(op[i] == 1) {
            cout << i - 1 - cnt << endl;
            cnt++;
        }
    }

    _rep(i, 2, N) {
        if(op[i] == -1) cout << 1 << endl;
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &N, &T);
    _rep(i, 1,N) scanf("%d", &A[i]);

    initdp();
    dp();
    out(T);
}