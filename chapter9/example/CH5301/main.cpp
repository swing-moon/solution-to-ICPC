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

const int maxn = 300 + 5;
const int inf = 0x3f;
int A[maxn];
int N;
int f[maxn][maxn];
int sum[maxn];

void initdp() {
    Set(sum, 0);
    Set(f, inf);
    _rep(i, 1, N) {
        sum[i] = sum[i - 1] + A[i];
        assert(sum[i] != 0);
        f[i][i] = 0;
    }
}

void dp() {
    _rep(len, 2, N) _rep(l, 1, N - len + 1) {
        int r = l + len - 1;
        for(int k = l; k < r; k++) f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);

        f[l][r] += (sum[r] - sum[l - 1]);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &N);
    _rep(i, 1, N) {
        scanf("%d", &A[i]);
        //debug(A[i]);
    }

    initdp();
    dp();

    printf("%d\n", f[1][N]);
}