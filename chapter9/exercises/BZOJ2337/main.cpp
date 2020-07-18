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

const int maxn = 100 + 10;
const int maxm = 10000 + 10;
double A[maxn][maxn];
double K[maxn];
int N, M;

class Graph {
public:
    int tot;
    int head[maxn], ver[maxm << 1], nxt[maxm << 1], w[maxm << 1];
    void clear() {
        tot = 1;
        Set(head, 0);
        Set(ver, 0);
        Set(nxt, 0);
        Set(w, 0);
    }

    void add(int x, int y, int z) {
        ver[++tot] = y;
        w[tot] = z;

        nxt[tot] = head[x];
        head[x] = tot;
    }
};

Graph G;

void init() {
    G.clear();
    Set(A, 0);
    Set(K, 0);
}

void Gauss() {
    _rep(i, 1, N) {
        int r = i;
        _rep(j, i + 1, N) if(fabs(A[j][i]) > fabs(A[r][i])) r = j;
        if(r != i) _rep(k, 1, N + 1) swap(A[i][k], A[r][k]);

        double t = A[i][i];
        _rep(k, i + 1, N + 1) A[i][k] /= t;

        _rep(j, 1, N) if(i != j) {
            double t = A[j][i];
            _rep(k, 1, N + 1) A[j][k] -= t * A[i][k];
        }
    }
}

double build() {
    double ans = 0.0;
    _for(i, 0, 30) {
        Set(A, 0);
        _for(u, 1, N) {
            A[u][u] = 1.0;
            for(int e = G.head[u]; e; e = G.nxt[e]) {
                int v = G.ver[e];

                if((1 << i) & G.w[e]) A[u][v] += 1.0 / K[u], A[u][N + 1] += 1.0 / K[u];
                else A[u][v] -= 1.0 / K[u];
            }
        }
        A[N][N] = 1.0;
        Gauss();
        ans += A[1][N + 1] * (double)(1 << i);
    }

    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &N, &M);
    _rep(i, 1, M) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G.add(u, v, w);
        K[u] += 1.0, K[v] += 1.0;
        if(u == v) K[u] -= 1.0;
        else G.add(v, u, w);
    }
    // then build matrix
    printf("%.3lf\n", build());
}