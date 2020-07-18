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

const int maxn = 1000 + 5;
const int maxm = 20 + 5;
const int inf = 0x3f3f3f3f;
int n, m;

int D[maxn][maxm], inq[maxn][maxm];
typedef pair<int, int> PII;
int C[maxn];

// == run spfa ==
void initSpfa() {
    Set(inq, 0);
    Set(D, inf);
}

void spfa(int st_x, int st_j) {
    queue<PII> que;
    que.push(MPR(st_x, st_j));
    D[st_x][st_j] = 0;
    inq[st_x][st_j] = 1;

    while (!que.empty()) {
        int x = que.front().first;
        int j = que.front().second;
        que.pop();
        inq[x][j] = 0;

        _rep(i, 1, m) {
            int nx = x + C[i];
            int w = abs(i - j) + 2 * abs(C[i]);
            if(nx < 1 || nx > n) continue;

            if(D[nx][i] > D[x][j] + w) {
                D[nx][i] = D[x][j] + w;
                if(!inq[nx][i]) {
                    que.push(MPR(nx, i));
                    inq[nx][i] = 1;
                }
            }
        }
    }
}
// == spfa finsihed ==

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    int pos = 0;
    _rep(i, 1, m) {
        scanf("%d", &C[i]);
        if(C[i] == 0) pos = i;
    }

    // then spfa
    initSpfa();
    spfa(1, pos);

    int ans = inf;
    _rep(i, 1, m) ans = min(ans, D[n][i]);

    if(ans == inf) puts("-1");
    else printf("%d\n", ans);
}