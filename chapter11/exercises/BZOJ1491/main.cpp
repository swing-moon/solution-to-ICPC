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

int d[maxn][maxn];
ll c[maxn][maxn];
double ans[maxn];

void initFloyd() {
    Set(d, inf);
    _rep(i, 0, n) d[i][i] = 0;

    Set(c, 0);
    Set(ans, 0.0);
}

void floyd() {
    _rep(k, 1, n) _rep(i, 1, n) _rep(j, 1, n) {
        if(i != j && k != i && k != j) {
            if(d[i][j] > d[i][k] + d[k][j]) {
                d[i][j] = d[i][k] + d[k][j];
                c[i][j] = 1ll * c[i][k] * c[k][j];
            }
            else if(d[i][j] == d[i][k] + d[k][j]) {
                c[i][j] += 1ll * c[i][k] * c[k][j];
            }
        }
    }
}

void solve() {
    _rep(k, 1, n) _rep(i, 1, n) _rep(j, 1, n) {
        if(i != j && k != i && k != j) {
            if(d[i][j] == d[i][k] + d[k][j]) {
                ans[k] += (double) c[i][k] * c[k][j] / c[i][j];
            }
        }
    }
    _rep(i, 1, n) printf("%.3lf\n", ans[i]);
}


int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);

    initFloyd();

    _for(i, 0, m) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        d[x][y] = d[y][x] = z;
        c[x][y] = c[y][x] = 1ll;
    }

    floyd();
    solve();
}