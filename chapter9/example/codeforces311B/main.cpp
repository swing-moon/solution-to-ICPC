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
#define MPR(a, b) make_pair(a, b)

const int maxn = 100000 + 10;
const int maxm = 100 + 10;
const int inf = 0x3f;
llong f[maxm][maxn], D[maxn], H[maxn], T[maxn], q[maxn];
llong g[maxn];
int N, M, P;
llong A[maxn], S[maxn];

void init() {
    sort(A + 1, A + 1 + M);
    _rep(i, 1, M) {
        S[i] = S[i - 1] + A[i];
    }
    Set(f, inf);
    Set(g, 0);
    Set(q, 0);
    f[0][0] = 0;
}

void solve() {
    _rep(i, 1, P) {
        _rep(k, 1, M) g[k] = f[i - 1][k] + S[k];

        int l = 1, r = 1;
        q[1] = 0;

        _rep(j, 1, M) {
            while (l < r && (g[q[l+1]] - g[q[l]]) <= (A[j] * (q[l+1] - q[l]) ) ) l++;
            f[i][j] = min(f[i - 1][j], g[q[l]] + A[j] * (j - q[l]) - S[j] );

            while (l < r && ( (g[q[r]] - g[q[r-1]]) * (j - q[r]) >= (g[j] - g[q[r]]) * (q[r] - q[r-1]) ) ) r--;
            q[++r] = j;
        }
    }
    cout << f[P][M] << endl;
}

int main() {
    freopen("input.txt", "r", stdin);

    // == input ==
    cin >> N >> M >> P;
    _rep(i, 2, N) {
        int x;
        scanf("%d", &x);
        D[i] = D[i - 1] + x;
    }

    _rep(i, 1, M) {
        int h, t;
        scanf("%d%d", &h, &t);
        A[i] = t - D[h];
    }
    // == input finished ==

    // == init data ==
    init();
    // == init data finished ==

    // == solve the problem ==
    solve();
}