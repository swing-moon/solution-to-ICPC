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

const int maxd = 30 + 5;
const int maxn = 10 + 5;
const int mod = 11380;

int f[maxd][maxn][maxn][maxn];
int D, L1, L2, L3;

void initdp() {
    Set(f, 0);
    _rep(d, 0, D) f[d][0][0][0] = 1;
}

void dp() {
    _rep(d, 1, D) {
        _rep(l1, 0, L1) _rep(l2, 0, L2) _rep(l3, 0, L3) {
            if(!l1 && !l2 && !l3) continue;
            int sum = 0;
            _rep(p, 1, l1) _rep(q, 0, l2) _rep(r, 0, l3) sum = (sum + (f[d-1][p-1][q][r] * f[d][l1-p][l2-q][l3-r] % mod)) % mod;
            _rep(q, 1, l2) _rep(r, 0, l3) sum = (sum + (f[d-1][0][q-1][r] * f[d][l1][l2-q][l3-r]) % mod) % mod;
            _rep(r, 1, l3) sum = (sum + (f[d-1][0][0][r-1] * f[d][l1][l2][l3-r]) % mod) % mod;

            f[d][l1][l2][l3] = sum;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d%d%d", &L1, &L2, &L3, &D);

    initdp();
    if(D == 0) {
        if(!L1 && !L2 && !L3) puts("1");
        else puts("0");

        return 0;
    }

    // then dp()
    dp();
    printf("%d\n", (f[D][L1][L2][L3] - f[D-1][L1][L2][L3] + mod) % mod);
}