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

const int maxn = 4000;
const int inf = 0x3f3f3f3f;
int N, B;
int U[maxn];

int f[2][maxn][2];

void init() {
    Set(f, -inf);
}

void initdp1() {
    f[1 & 1][1][1] = f[1 & 1][0][0] = 0;
}

void initdp2() {
    f[1 & 1][1][1] = U[1];
}

int dp1() {
    _rep(i, 2, N) _rep(j, 0, B) {
        f[i & 1][j][0] = max(f[(i - 1) & 1][j][0], f[(i - 1) & 1][j][1]);
        if(j - 1 >= 0) f[i & 1][j][1] = max(f[(i - 1) & 1][j - 1][0], f[(i - 1) & 1][j - 1][1] + U[i]);
    }
    return max(f[N & 1][B][0], f[N & 1][B][1]);
}

int dp2() {
    _rep(i, 2, N) _rep(j, 0, B) {
            f[i & 1][j][0] = max(f[(i - 1) & 1][j][0], f[(i - 1) & 1][j][1]);
            if(j - 1 >= 0) f[i & 1][j][1] = max(f[(i - 1) & 1][j - 1][0], f[(i - 1) & 1][j - 1][1] + U[i]);
    }

    return f[N & 1][B][1];
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &N, &B);

    _rep(i, 1, N) scanf("%d", &U[i]);
    if(B == 0) {
        printf("0");
        return 0;
    }

    init();
    initdp1();
    int ans1 = dp1();

    init();
    initdp2();
    int ans2 = dp2();

    printf("%d", max(ans1, ans2));
}