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

const int maxn = 5000 + 10;
char p[maxn], q[maxn];
const int inf = 0x3f3f3f3f;

int f[2][maxn], cnt[2][maxn];
int N, M;
int sp[256 + 5], ep[256 + 5], sq[256 + 5], eq[256 + 5];
int k = 0;

void init() {
    Set(sp, inf);
    Set(sq, inf);
    Set(ep, 0);
    Set(eq, 0);
    N = strlen(p + 1);
    M = strlen(q + 1);

    _rep(i, 1, N) {
        sp[p[i]] = min(sp[p[i]], i);
        ep[p[i]] = i;
        //debug(ep[p[i]]);
    }
    _rep(i, 1, M) {
        sq[q[i]] = min(sq[q[i]], i);
        eq[q[i]] = i;
    }
}

void initdp() {
    Set(f, 0);
    Set(cnt, 0);

    k = 0;
}

void dp() {
    _rep(i, 0, N) {
        _rep(j, 0, M) {
            //
            if(i == 0 && j == 0) continue;

            int v1 = inf, v2 = inf;
            if(i) v1 = f[k ^ 1][j] + cnt[k ^ 1][j];
            if(j) v2 = f[k][j - 1] + cnt[k][j - 1];
            f[k][j] = min(v1, v2);

            if(i) {
                // Move p[i]
                cnt[k][j] = cnt[k ^ 1][j];
                if(i == sp[p[i]] && j < sq[p[i]]) cnt[k][j]++;
                if(i == ep[p[i]] && j >= eq[p[i]]) cnt[k][j]--;
            }
            else if(j) {
                // Move q[j]
                cnt[k][j] = cnt[k][j - 1];
                if(j == sq[q[j]] && i < sp[q[j]]) cnt[k][j]++;
                if(j == eq[q[j]] && i >= ep[q[j]]) cnt[k][j]--;
            }
        }
        k ^= 1;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%s", p + 1);
        scanf("%s", q + 1);
        init();
        //debug(p[1]);
        //debug(ep['A']);
        assert(ep[p[1]] != 0);

        initdp();
        dp();

        printf("%d\n", f[k ^ 1][M]);
    }
}