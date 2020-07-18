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

const int maxn = 100 + 2;
int f[maxn * 2][maxn * 2];
int e[maxn * 2];
int N;

void initdp() {
    Set(f, 0);
}

void dp() {
    _rep(len, 1, N) for(int i = 1; i + len - 1 <= (N << 1); i++) {
        int j = i + len - 1;

        _for(k, i, j) {
            f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + e[i] * e[k + 1] * e[j + 1]);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &N) != EOF) {
        _rep(i, 1, N) scanf("%d", &e[i]);
        _rep(i, N + 1, (N << 1)) e[i] = e[i - N];

        //_rep(i, 1, 2*N) printf("%d ", e[i]);

        initdp();
        dp();

        int ans = 0;
        _rep(i, 1, N) ans = max(ans, f[i][i + N - 1]);

        printf("%d\n", ans);
    }
}