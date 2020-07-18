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

const int maxn = 100 + 10;
const int inf = 0x3f3f3f3f;
int n, m;

// == floyd graph ==
int f[maxn][maxn];

void initFloyd() {
    Set(f, inf);
    _rep(i, 0, n) f[i][i] = 0;
}

void floyd() {
    _rep(k, 1, n) _rep(i, 1, n) _rep(j, 1, n) {
        f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    }
}
// == floyd finsihed ==

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);

    initFloyd();

    _for(i, 0, m) {
        int x, y;
        scanf("%d%d", &x, &y);
        f[x][y] = f[y][x] = 1;
    }

    floyd();

    int ans = 0;
    _rep(i, 1, n) _rep(j, i + 1, n) {
        ans = max(ans, f[i][j]);
    }
    cout << ans << endl;
}