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

const int maxn = 100000 + 10;

// == define Edge and Graph ==
class Edge {
public:
    int to;
    Edge() {}
    Edge(int to) : to(to) {}
};

vector<Edge> edges;
vector<int> G[maxn];
// == Edge and Graph finsihed ==

// == tarjan info ==
int n, m;
vector<int> dcc[maxn];
int dfn[maxn], low[maxn], cnt = 0, Clock = 0;
bool cut[maxn];

stack<int> stk;
int root = 0;

void init() {
    cnt = 0;
    Clock = 0;
    root = 0;

    edges.clear();
    edges.push_back(Edge());
    edges.push_back(Edge());
    // NIL edges

    Set(dfn, 0);
    Set(low, 0);
    Set(cut, 0);

    while(!stk.empty()) stk.pop();
}
// == tarjan info finished ==

// == tarjan main ==
void addEdge(int u, int v) {
    edges.push_back(Edge(v));
    G[u].push_back(edges.size() - 1);
}

void tarjan(int u) {
    dfn[u] = low[u] = ++Clock;
    stk.push(u);

    if(u == root && G[u].size() == 0) {
        // single point
        dcc[++cnt].push_back(u);
        return;
    }

    int cld = 0;
    _for(i, 0, G[u].size()) {
        int eid = G[u][i], v = edges[eid].to;

        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);

            // judge cut-point
            if(low[v] >= dfn[u]) {
                cld++;
                if(u != root || cld > 1) cut[u] = true;

                // save the point in the same DCC
                cnt++;
                for(;;) {
                    int z = stk.top(); stk.pop();
                    dcc[cnt].push_back(z);
                    if(z == v) break;
                }
                dcc[cnt].push_back(u);
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
}
// == tarjan finsihed ==

// == vDCC Graph ==
vector<int> GC[maxn];
vector<Edge> vDCC;
int belong[maxn], newID[maxn];
int num = 0;

void initDCC() {
    vDCC.clear();
    vDCC.push_back(Edge());
    vDCC.push_back(Edge());
    // NIL edges

    Set(belong, 0);
    Set(newID, 0);
    num = 0;
}

void add_c(int u, int v) {
    vDCC.push_back(Edge(v));
    GC[u].push_back(vDCC.size() - 1);
}

// == vDCC finsihed ==

void getDCC() {
    // input DCC nodes and data
    _rep(i, 1, cnt) {
        printf("v-DCC #%d:", i);
        _for(j, 0, dcc[i].size()) {
            printf(" %d", dcc[i][j]);
        }
        puts("");
    }

    // point reduction
    num = cnt;
    _rep(i, 1, n) if(cut[i]) newID[i] = ++num;

    // build new Graph for vDCC
    _rep(i, 1, cnt) _for(j, 0, dcc[i].size()) {
        int z = dcc[i][j];
        if(cut[z]) {
            add_c(i, newID[z]), add_c(newID[z], i);
        }
        else belong[z] = i;
    }

    // print info
    printf("缩点之后的森林，点数 %d, 边数 %d\n", num, (int)(vDCC.size() - 1) >> 1);
    printf("下图编号 1～%d 的为原图的v-DCC，编号 >=%d 的为原图的割点\n", cnt, cnt);
    for(int i = 2; i < vDCC.size(); i += 2) {
        printf("vDCC#%d  <----->  vDCC#%d\n", vDCC[i^1].to, vDCC[i].to);
    }
}
// == vDCC Graph finished ==

int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> m;

    init();
    _rep(i, 1, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        if(u == v) continue;
        addEdge(u, v), addEdge(v, u);
    }

    // == tarjan ==
    _rep(i, 1, n) if(!dfn[i]) {
        root = i, tarjan(i);
    }
    _rep(i, 1, n) if(cut[i]) printf("%d ", i);
    puts("are cut vertexes");
    // == tarjan finished ==

    initDCC();
    getDCC();
}