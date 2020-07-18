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

const int maxn = 1500 + 5;
int hasFa[maxn];
int f[maxn][2];
vector<int> son[maxn];
int N;

void init() {
    Set(hasFa, 0);
    Set(f, 0);
    _for(i, 0, maxn) son[i].clear();
}

void dp(int u) {
    f[u][0] = 0;
    f[u][1] = 1;
    _for(i, 0, son[u].size()) {
        int v = son[u][i];
        dp(v);
        f[u][0] += f[v][1];
        f[u][1] += (min(f[v][0], f[v][1]));
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &N) != EOF) {
        init();
        _for(i, 0, N) {
            int u, k;
            scanf("%d:(%d)", &u, &k);
            _for(j, 0, k) {
                int v;
                scanf("%d", &v);
                son[u].push_back(v);
                hasFa[v] = 1;
            }
        }
        // then input finished
        int r = 0;
        _for(i, 0, N) if(!hasFa[i]) { r = i; break; }

        dp(r);
        printf("%d\n", min(f[r][0], f[r][1]));
    }
}