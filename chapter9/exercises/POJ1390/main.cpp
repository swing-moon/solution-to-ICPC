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

const int maxn = 200 + 10;
int f[maxn][maxn][maxn];
int A[maxn];
int N;

void init() {
    Set(f, -1);
}

int dp(int i, int j, int k) {
    if(i > j) return 0;
    int& ans = f[i][j][k];
    if(i == j) return ans = (1 + k) * (1 + k);
    if(ans >= 0) return ans;

    int p = j;
    while (p >= i && A[p] == A[j]) p--;
    p++;

    ans = dp(i, p-1, 0) + (k + j-p+1) * (k + j-p+1);
    _for(q, i, p) {
        if(A[q] == A[j] && A[q+1] != A[q]) {
            ans = max(ans, dp(i, q, k+j-p+1) + dp(q+1, p-1, 0));
        }
    }

    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    _rep(kase, 1, T) {
        printf("Case %d: ", kase);
        scanf("%d", &N);
        _rep(i, 1, N) scanf("%d", &A[i]);
        init();

        // then dp()
        printf("%d\n", dp(1, N, 0));
    }
}