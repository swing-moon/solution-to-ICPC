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

int n, m, q;
int d[maxn][maxn];

void init() {
    Set(d, 0);
    _rep(i, 1, n) _rep(j, 1, n) d[i][j] = inf;
    _rep(i, 1, n) d[i][i] = 0;
}

void floyd() {
    _rep(k, 1, n) _rep(i, 1, n) _rep(j, 1, n) {
        if(d[i][k] < inf && d[k][j] < inf) {
            d[i][j] = min(d[i][j], max(d[i][k], d[k][j]));
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;
    while (scanf("%d%d%d", &n, &m, &q) == 3 && n) {
        init();

        while (m--) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);

            d[x][y] = d[y][x] = min(d[x][y], z);
        }

        // run floyd()
        floyd();

        if(kase > 0) printf("\n");
        printf("Case #%d\n", ++kase);

        // query
        while (q--) {
            int q1, q2;
            scanf("%d%d", &q1, &q2);
            if(d[q1][q2] == inf) printf("no path\n");
            else printf("%d\n", d[q1][q2]);
        }
    }
}