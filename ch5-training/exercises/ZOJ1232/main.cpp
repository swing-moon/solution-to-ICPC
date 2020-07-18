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
typedef long long ll;
typedef set<int>::iterator ssii;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
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
#define MPR(a, b) make_pair(a, b)

const int inf = 0x3f3f3f3f;
const int maxn = 100 + 10;
int D[maxn][maxn];
int valid[maxn][maxn];
int a, b, m, L, K;

void init() {
    Set(D, inf);
    _for(i, 0, maxn) D[i][i] = 0;

    Set(valid, 0);
}

void build() {
    _for(i, 0, m) {
        int u, v, L;
        scanf("%d%d%d", &u, &v, &L);
        D[u][v] = D[v][u] = min(D[v][u], L);
    }
}

void floyd() {
    _rep(k, 1, a+b) _rep(i, 1, a+b) _rep(j, 1, a+b) {
        if(D[i][j] > D[i][k] + D[k][j]) {
            D[i][j] = D[i][k] + D[k][j];
        }
        if(k <= a && D[i][j] <= L) valid[i][j] = 1;
    }
}

// == dp ==
const int st = 1;
int dp[maxn][maxn];

void initDP() {
    Set(dp, inf);
    _rep(i, 1, a+b) dp[i][0] = D[st][i];
    _rep(k, 0, K) dp[st][k] = 0;
}

void solve() {
    _rep(i, 1, a+b) _rep(k, 1, K) {
        _for(j, 1, i) {
            if(valid[i][j] == 1)
                dp[i][k] = min(dp[i][k], dp[j][k - 1]);
            dp[i][k] = min(dp[i][k], dp[j][k] + D[j][i]);
        }
    }
}
// == dp finished ==

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);

    while (kase--) {
        init();
        scanf("%d%d%d%d%d", &a, &b, &m, &L, &K);

        // build
        build();

        // floyd
        floyd();

        // dp
        initDP();
        solve();

        printf("%d\n", dp[a+b][K]);
    }
}