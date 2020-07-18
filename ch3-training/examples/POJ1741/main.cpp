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

const int maxn = 1e5 + 10;
const int inf = 0x3f3f3f3f;
int n, k;

// == Graph definition ==
int M = 0;
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
    M = 0;
    memset(head, 0, sizeof(head));
}

void add(int u, int v, int w) {
    edges[++M] = Edge(v, w);
    edges[M].next = head[u];
    head[u] = &edges[M];
}
// == Graph finsiehd ==

// == find gravity as root ==
int root = 0;
int sz[maxn];
int vis[maxn];
int sn = n;

void getRoot(int x, int pa, int& res) {
    sz[x] = 1;
    int maxpart = 0;
    for(const Edge *e = head[x]; e; e = e->next) {
        int y = e->to;
        int w = e->weight;

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
// == gravity finished ==


// == work ==
int dep[maxn];

void getDep(int x, int pa, vector<int>& vec) {
    vec.push_back(dep[x]);
    for(const Edge *e = head[x]; e; e = e->next) {
        int y = e->to;
        int w = e->weight;

        if(vis[y] || y == pa) continue;
        dep[y] = dep[x] + w;

        getDep(y, x, vec);
    }
}

inline int cal(int x) {
    vector<int> vec;
    getDep(x, 0, vec);
    sort(vec.begin(), vec.end());

    int l = 0, r = vec.size() - 1;
    int sum = 0;
    while (l < r) {
        if(vec[l] + vec[r] <= k) sum += r - l, l++;
        else r--;
    }
    return sum;
}

void work(int x, int &ans) {
    dep[x] = 0;
    vis[x] = 1;
    ans += cal(x);

    for(const Edge *e = head[x]; e; e = e->next) {
        int y = e->to;
        int w = e->weight;
        if(vis[y]) continue;

        dep[y] = dep[x] + w;
        ans -= cal(y);
        //debug(ans);

        sn = sz[y];
        root = 0;
        int res = inf;
        getRoot(y, 0, res);

        work(root, ans);
    }
}
// == work finsihed ==

void init() {
    //
    root = 0;
    Set(sz, 0);
    Set(vis, 0);
    sn = n;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &n, &k) == 2 && n) {
        // get data
        initG();
        init();

        _for(i, 1, n) {
            int x, y, w;
            scanf("%d%d%d", &x, &y, &w);
            add(x, y, w);
            add(y, x, w);
        }

        // get data finished

        // then solve the problem
        int res = inf;
        getRoot(1, 0, res);

        int ans = 0;
        work(root, ans);
        printf("%d\n", ans);
    }
}