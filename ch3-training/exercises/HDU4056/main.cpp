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
#define MPR(a, b) make_pair(a, b)

const int maxn = 50000 + 10;
const double eps = 1e-7;
int n, m, q;

class Node {
public:
    char cmd[10];
    int xc, yc, r, w, l, c;
} A[maxn];

int ans[10];

// == union set ==
int pa[maxn];
bool vis[maxn];

void initpa() {
    Set(vis, 0);
    _for(j, 0, m) pa[j] = j;
}

int findset(int x) {
    return x == pa[x] ? x : pa[x] = findset(pa[x]);
}
// == union set finished ==

void init() {
    Set(ans, 0);
}

// == solve the problem ==
void solve() {
    _for(i, 0, n) {
        initpa();

        _forDown(j, q - 1, 0) {
            const Node& cur = A[j];
            int color = cur.c;
            int l, r;

            // == get geo ==
            if(cur.cmd[0] == 'C') {
                if((cur.r) * (cur.r) < (i-cur.xc) * (i-cur.xc)) continue;
                int dy = (int) (sqrt((cur.r) * (cur.r) - (i-cur.xc) * (i-cur.xc)) + eps);
                l = cur.yc - dy, r = cur.yc + dy;
            }
            else if(cur.cmd[0] == 'D') {
                if((i > cur.xc + cur.r) || (i < cur.xc - cur.r)) continue;
                int dy = cur.r - abs(i - cur.xc);
                l = cur.yc - dy;
                r = cur.yc + dy;
            }
            else if(cur.cmd[0] == 'R') {
                if((i < cur.xc) || (i > cur.xc + cur.l - 1)) continue;
                l = cur.yc;
                r = cur.yc + cur.w - 1;
            }
            else {
                if((i < cur.xc) || (i > cur.xc + (cur.w+1)/2 - 1)) continue;
                int dy = cur.w - 2*(i - cur.xc);
                l = cur.yc - dy / 2;
                r = cur.yc + dy / 2;
            }
            // == get geo finsihed ==

            l = max(l, 0);
            r = min(r, m - 1);

            int fl = findset(l);
            int fk;
            for(int k = r; k >= l; ) {
                fk = findset(k);

                if(!vis[fk]) ans[color]++;
                vis[fk] = true;

                if(fk != fl) pa[fk] = fl;

                k = fk - 1;
            }
        }
    }
}
// == solve finsihed ==

// == get input ==
void inp() {
    while (~scanf("%d%d%d", &n, &m, &q)) {
        init();
        _for(i, 0, q) {
            scanf("%s%d%d", A[i].cmd, &A[i].xc, &A[i].yc);
            if(A[i].cmd[0] == 'C' || A[i].cmd[0] == 'D') scanf("%d%d", &A[i].r, &A[i].c);
            else if(A[i].cmd[0] == 'R') scanf("%d%d%d", &A[i].l, &A[i].w, &A[i].c);
            else if(A[i].cmd[0] == 'T') scanf("%d%d", &A[i].w, &A[i].c);
        }

        solve();

        _rep(i, 1, 9) {
            if(i != 1) printf(" ");
            printf("%d", ans[i]);
        }
        cout << endl;
    }
}
// == input finished ==

int main() {
    freopen("input.txt", "r", stdin);

    inp();
}