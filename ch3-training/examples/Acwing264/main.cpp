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
#define Cpy(a, b) memcpy(a, b, sizeof(b))
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

const int maxn = 1e6 + 10;
const int inf = 0x3f3f3f3f;
int N, K;

// == Graph definition ==
int m = 0;

class Edge {
public:
    int to, weight;
    Edge *next;

    Edge() {}
    Edge(int to, int w) : to(to), weight(w) {
        next = NULL;
    }
} edges[maxn << 1], *head[maxn];

void initG() {
    m = 0;
    memset(head, 0, sizeof(head));
}

void add(int u, int v, int w) {
    edges[++m] = Edge(v, w);
    edges[m].next = head[u];
    head[u] = &edges[m];
}
// == Graph finished ==

// == get root ==
int root = 0;
int sn = N;
int sz[maxn];
int vis[maxn];

void getRoot(int x, int pa, int &res) {
    sz[x] = 1;

    int maxpart = 0;
    for(const Edge *e = head[x]; e; e = e->next) {
        int y = e->to;
        if(vis[y] || y == pa) continue;

        getRoot(y, x, res);

        sz[x] += sz[y];
        maxpart = max(maxpart, sz[y]);
    }
    maxpart = max(maxpart, sn - sz[x]);

    if(maxpart < res) {
        res = maxpart;
        root = x;
    }
}
// == get root finished ==

// == solve ==
int dep[maxn];
int D[maxn];
int dp[maxn];

void dfs(int x, int pa, vector<int> &vec1, vector<int> &vec2) {
    vec1.push_back(D[x]);
    vec2.push_back(dep[x]);
    for(const Edge *e = head[x]; e; e = e->next) {
        int y = e->to;
        int w = e->weight;

        if(vis[y] || y == pa) continue;

        dep[y] = dep[x] + 1;
        D[y] = D[x] + w;

        if(D[y] <= 1e6) dfs(y, x, vec1, vec2);
    }
}

queue<int> que;
void cal(int x, int &ans) {
    for(const Edge *e = head[x]; e; e = e->next) {
        int y = e->to;
        int w = e->weight;

        if(vis[y]) continue;

        vector<int> vec1, vec2;
        dep[y] = dep[x] + 1;
        D[y] = D[x] + w;
        dfs(y, x, vec1, vec2);

        _for(i, 0, vec1.size()) {
            if(K >= vec1[i]) ans = min(ans, dp[K - vec1[i]] + vec2[i]);
        }

        _for(i, 0, vec1.size()) {
            que.push(vec1[i]);
            dp[vec1[i]] = min(dp[vec1[i]], vec2[i]);
        }
    }
    while (que.size()) {
        dp[que.front()] = inf;
        que.pop();
    }
}

void solve(int x, int &ans) {
    vis[x] = 1;
    dep[x] = 0;
    D[x] = 0;
    dp[0] = 0;

    cal(x, ans);

    for(const Edge *e = head[x]; e; e = e->next) {
        int y = e->to;
        int w = e->weight;

        if(vis[y]) continue;

        sn = sz[y];
        root = 0;
        int res = inf;
        getRoot(y, x, res);

        solve(root, ans);
    }
}
// == solve finished ==

void init() {
    root = 0;
    sn = N;
    Set(sz, 0);
    Set(vis, 0);
    Set(dep, 0);
    Set(D, 0);
    Set(dp, inf);
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &N, &K);
    initG();
    init();

    _for(i, 1, N) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u++; v++;
        add(u, v, w);
        add(v, u, w);
    }

    // then solve the problem
    int res = inf;
    getRoot(1, -1, res);
    int ans = inf;
    solve(root, ans);

    if(ans == inf) printf("-1\n");
    else printf("%d\n", ans);
}