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

const int maxn = 500 + 10;
int f[maxn][maxn];
int A[maxn], B[maxn];
int n, m;

void init() {
    Set(f, 0);
}

int LCIS() {
    _rep(i, 1, n) {
        int maxv = 0;
        if(B[0] < A[i]) maxv = f[i - 1][0];

        _rep(j, 1, m) {
            if(A[i] == B[j]) f[i][j] = maxv + 1;
            else f[i][j] = f[i - 1][j];

            if(B[j] < A[i]) maxv = max(maxv, f[i - 1][j]);
        }
    }

    int res = 0;
    _rep(i, 1, m) res = max(f[n][i], res);
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);

    while (kase--) {
        init();
        scanf("%d", &n);
        _rep(i, 1, n) scanf("%d", &A[i]);

        scanf("%d", &m);
        _rep(i, 1, m) scanf("%d", &B[i]);

        int ans = LCIS();
        printf("%d\n", ans);
        if(kase) printf("\n");
    }
}
