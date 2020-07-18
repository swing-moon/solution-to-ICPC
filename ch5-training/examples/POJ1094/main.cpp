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
typedef long long ll;
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
#define MPR(a, b) make_pair(a, b)

const int maxn = 30;
int f[maxn][maxn], G[maxn][maxn];
int deg[maxn];
int n, m;
char str[5];

void init() {
    Set(f, 0);
    Set(G, 0);
    Set(deg, 0);
}

// == floyd algorithm ==
void floyd() {
    _for(k, 0, n) _for(i, 0, n) _for(j, 0, n) {
        f[i][j] |= (f[i][k] & f[k][j]);
    }
}
// == floyd finsihed ==

// == topo sort ==
void topo(const int t) {
    queue<int> que;
    _for(i, 0, n) if(deg[i] == 0) que.push(i);
    printf("Sorted sequence determined after %d relations: ", t);

    while (!que.empty()) {
        int x = que.front(); que.pop();
        printf("%c", (char)('A' + x));
        _for(y, 0, n) {
            if(G[x][y]) if(--deg[y] == 0) que.push(y);
        }
    }
    printf(".\n");
}
// == topo finsihed ==

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) && n) {
        init();

        bool found = false, fail = false;
        int t = 0;
        _rep(i, 1, m) {
            scanf("%s", str);
            if(found || fail) continue;

            int u = str[0] - 'A';
            int v = str[2] - 'A';
            G[u][v] = f[u][v] = 1;
            deg[v]++;
            floyd();

            found = true;
            _for(u, 0, n) {
                if(f[u][u]) {
                    fail = true;
                    break;
                }
                _for(v, 0, n) {
                    if(v != u && (f[u][v] ^ f[v][u]) == 0) found = false;
                }
            }
            t = i;
        }
        if(fail) printf("Inconsistency found after %d relations.\n", t);
        else if(found) topo(t);
        else printf("Sorted sequence cannot be determined.\n");
    }
}