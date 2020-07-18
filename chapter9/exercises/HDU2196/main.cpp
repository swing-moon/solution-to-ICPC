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

const int maxn = 10000 + 10;
int f1[maxn], f12nd[maxn], f2[maxn];
int pass[maxn];

int N;

class Graph {
public:
    int tot;
    int head[maxn], ver[maxn * 2], nxt[maxn * 2];
    int w[maxn * 2];

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
    Set(f1, -1);
    Set(f12nd, -1);
    Set(f2, -1);
    Set(pass, 0);
    G.clear();
}

bool vis[maxn];

void initvis() {
    Set(vis, 0);
}

void dp1(int u) {
    if(f1[u] >= 0) return;
    f1[u] = f12nd[u] = f2[u] = pass[u] = 0;
    vis[u] = 1;

    for(int e = G.head[u]; e; e = G.nxt[e]) {
        int v = G.ver[e];
        if(vis[v]) continue;

        //debug(v);

        dp1(v);

        if(f1[u] < f1[v] + G.w[e]) {
            f12nd[u] = max(f12nd[u], f1[u]);
            f1[u] = f1[v] + G.w[e];
            pass[u] = v;
        }
        else if(f12nd[u] < f1[v] + G.w[e]) {
            f12nd[u] = f1[v] + G.w[e];
        }
    }
    return;
}

void dp2(int u) {
    vis[u] = 1;
    for(int e = G.head[u]; e; e = G.nxt[e]) {
        int v = G.ver[e];
        if(vis[v]) continue;

        if(v == pass[u]) {
            // u - v is the segment of longest path
            f2[v] = max(f2[u], f12nd[u]) + G.w[e];
        }
        else f2[v] = max(f1[u], f2[u]) + G.w[e];
        dp2(v);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &N) == 1 && N) {
        init();
        _rep(i, 2, N) {
            int v, w;
            scanf("%d%d", &v, &w);
            G.add(i, v, w);
            G.add(v, i, w);
        }

        // then dp1 and dp2
        initvis();
        dp1(1);

        initvis();
        dp2(1);

        _rep(i, 1, N) printf("%d\n", max(f1[i], f2[i]));
    }
}