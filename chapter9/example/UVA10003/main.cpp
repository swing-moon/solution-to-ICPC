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
int A[maxn];
int f[maxn][maxn], vis[maxn][maxn];
int N, L;

void init() {
    Set(f, 0);
    Set(vis, 0);
    A[0] = 0;
    A[N + 1] = L;
}

int dp(int i, int j) {
    if(i >= j - 1) return 0;
    if(vis[i][j]) return f[i][j];

    vis[i][j] = 1;
    int& ans = f[i][j];
    ans = -1;

    _rep(k, i + 1, j - 1) {
        int v = dp(i, k) + dp(k, j) + A[j] - A[i];
        if(ans < 0 || v < ans) ans = v;
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &L, &N) == 2 && L) {
        init();

        _rep(i, 1, N) scanf("%d", &A[i]);
        printf("The minimum cutting is %d.\n", dp(0, N + 1));
    }
}