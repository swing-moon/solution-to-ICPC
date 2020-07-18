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

const int maxn = 1000 + 10;
const int inf = 0x3f;
char str[maxn];
int vis[maxn][maxn];
int pali[maxn][maxn];
int N;

void init() {
    //
    Set(vis, 0);
    Set(pali, 0);
}

int f[maxn];
void initdp() {
    N = strlen(str + 1);
    Set(f, inf);
    f[0] = 0;
    _rep(i, 1, N) f[i] = i;
}

int isPali(int i, int j) {
    if(i >= j) return 1;
    if(str[i] != str[j]) return 0;

    if(vis[i][j]) return pali[i][j];
    vis[i][j] = true;

    return pali[i][j] = isPali(i + 1, j - 1);
}

void dp() {
    _rep(i, 1, N) _for(j, 0, i) {
        if(isPali(j + 1, i)) f[i] = min(f[i], f[j] + 1);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    while (T--) {
        init();
        scanf("%s", str + 1);

        initdp();
        dp();

        printf("%d\n", f[N]);
    }
}