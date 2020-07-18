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

const int maxn = 5000 + 5;
const int inf = 0x3f3f3f3f;
int f[maxn];
int g[maxn];
int A[maxn];
int N;

void initdp() {
    Set(f, 0);
    Set(g, 0);
    A[0] = inf;
    g[0] = 1;
}

int dp() {
    _rep(i, 1, N) {
        _forDown(j, i - 1, 0) {
            if(A[j] > A[i]) f[i] = max(f[i], f[j] + 1);
        }
    }

    int ans = 0;
    _rep(i, 1, N) ans = max(ans, f[i]);
    return ans;
}

void dp2() {
    _rep(i, 1, N) {
        _for(j, 1, i) if(A[i] == A[j]) f[j] = -inf;

        _for(j, 0, i) if( (j == 0 || A[j] > A[i]) && f[i] == f[j] + 1) g[i] += g[j];
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &N);
    _rep(i, 1, N) scanf("%d", &A[i]);

    initdp();
    int res = dp();
    printf("%d ", res);

    dp2();
    int cnt = 0;
    _rep(i, 1, N) if(f[i] == res) cnt += g[i];
    printf("%d\n", cnt);
}