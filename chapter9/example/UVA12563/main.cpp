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

const int maxn = 50 + 5;
int N, T, kase;
const int inf = 0x3f3f3f3f;
int t[maxn];
int f[maxn][maxn * 180 + 678];
int ans = 0;

void initdp() {
    ans = 0;
    Set(f, -inf);
    f[0][T] = 0;
}

void dp() {
    // int res;
    _rep(i, 1, N) {
        _rep(j, 1, T) f[i][j] = f[i - 1][j];

        _rep(j, 1, T) {
            if(j + t[i] > T) continue;
            f[i][j] = max(f[i][j], f[i - 1][j + t[i]] + 1);

            ans = max(ans, f[i][j]);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &kase);

    _rep(cas, 1, kase) {
        printf("Case %d:", cas);
        scanf("%d%d", &N, &T);
        _rep(i, 1, N) scanf("%d", &t[i]);

        // then dp
        initdp();
        dp();
        int ret = 0;
        for(int j = 1; j <= T; j++) {
            if(f[N][j] == ans) {
                // ans = f[N][j];
                ret = j;
                break;
            }
        }

        printf(" %d %d\n", ans + 1, (T - ret) + 678);
    }
}