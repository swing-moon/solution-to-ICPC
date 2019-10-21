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

const int maxn = 1000 + 10;
const int maxp = 200 + 10;
const int inf = 0x3f3f3f3f;

int L, N;
int cost[maxp][maxp], P[maxn];
int F[maxn][maxp][maxp];

void init() {
    Set(P, 0);
    Set(cost, 0);
    Set(F, inf);
}

void initDP() {
    F[0][1][2] = 0;
    P[0] =3;
}

void dp(int& ans) {
    // debug(f[0])
    _for(i, 0, N) _rep(x, 1, L) _rep(y, 1, L) {
        //debug(F[0][x][y]);
        int z = P[i];

        if(x == z || y == z || x == y) continue;

        F[i + 1][x][y] = min(F[i + 1][x][y], F[i][x][y] + cost[z][P[i + 1]]);
        F[i + 1][P[i]][y] = min(F[i + 1][P[i]][y], F[i][x][y] + cost[x][P[i + 1]]);
        F[i + 1][x][P[i]] = min(F[i + 1][x][P[i]], F[i][x][y] + cost[y][P[i + 1]]);
    }

    _rep(x, 1, L) _rep(y, 1, L) {
        int z = P[N];
        if(x == z || y == z || x == y) continue;

        ans = min(ans, F[N][x][y]);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    while (T--) {
        init();

        scanf("%d%d", &L, &N);

        _rep(i, 1, L) _rep(j, 1, L) cin >> cost[i][j];
        _rep(i, 1, N) scanf("%d", &P[i]);

        // then input finished
        assert(cost[0][0] == 0);
        //assert(P[6] == 5);

        initDP();
        int ans = inf;
        dp(ans);
        cout << ans << endl;
    }
}