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

const int maxm = 100000 + 5, maxn = 1000 + 5;

int A[maxn], C[maxn];

int N2 = 1;
int N, M;
bitset<maxm> f;

void initdp() {
    N2 = 1;
    f &= 1;
    f[0] = 1;
}


int dp() {
    _rep(i, 1, N) {
        for(int p = 1; p <= C[i]; p <<= 1) {
            //
            f |= (f << (p * A[i]));
            C[i] -= p;
        }
        if(C[i]) f |= (f << (C[i] * A[i]));
    }

    int ans = 0;
    _rep(i, 1, M) if(f[i]) ans += f[i];
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &N, &M) == 2 && N) {
        _rep(i, 1, N) scanf("%d", &A[i]);
        _rep(i, 1, N) scanf("%d", &C[i]);

        // then dp
        initdp();

        cout << dp() << endl;
    }
}