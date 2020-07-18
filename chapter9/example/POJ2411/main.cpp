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

const int maxn = 11 + 1;
llong f[maxn][1 << maxn];
bool inS[1 << maxn];
int N, M;

void init() {
    Set(f, 0);
    f[0][0] = 1;
}

inline void cal() {
    _for(i, 0, 1 << M) {
        bool cnt = 0, hasOdd = 0;
        _for(k, 0, M) {
            if((i >> k) & 1) hasOdd |= cnt, cnt = 0;
            else cnt ^= 1;
        }
        inS[i] = hasOdd | cnt ? 0 : 1;
    }
}

void dp() {
    _rep(i, 1, N) _for(j, 0, 1 << M) {
        f[i][j] = 0;
        _for(k, 0, 1 << M) {
            if((j & k) == 0 && inS[j | k]) f[i][j] += f[i - 1][k];
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &N, &M) == 2 && N) {
        init();
        cal();

        dp();
        cout << f[N][0] << endl;
    }
}