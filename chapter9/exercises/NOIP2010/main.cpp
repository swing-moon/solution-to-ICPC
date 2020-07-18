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

const int maxn = 120 + 5;
const int maxA = 350 + 5;
const int maxm = 40 + 5;
int N, M;
int A[maxA];
int C[maxn];

int f[maxn][maxm][maxm][maxm];

void initdp() {
    Set(f, 0);
}

void dp() {
    _rep(i, 1, M) for(int l1 = 0; l1 <= C[1] && l1 <= M; l1++)
        for(int l2 = 0; l2 <= C[2] && l2 <= M - l1; l2++)
            for(int l3 = 0; l3 <= C[3] && l3 <= M - l1 - l2; l3++) {
                int& ans = f[i][l1][l2][l3];
                int l4 = i - l1 - l2 - l3;
                int u = 1 + l1 + 2 * l2 + 3 * l3 + 4 * l4;

                if(l4) ans = f[i - 1][l1][l2][l3];
                if(l1) ans = max(ans, f[i - 1][l1 - 1][l2][l3]);
                if(l2) ans = max(ans, f[i - 1][l1][l2 - 1][l3]);
                if(l3) ans = max(ans, f[i - 1][l1][l2][l3 - 1]);

                ans += A[u];
            }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &N, &M);

    _rep(i, 1, N) scanf("%d", &A[i]);
    _rep(i, 1, M) {
        int x;
        scanf("%d", &x);
        C[x]++;
    }

    // input finished, then dp
    initdp();
    dp();
    printf("%d\n", f[M][C[1]][C[2]][C[3]] + A[1]);
}