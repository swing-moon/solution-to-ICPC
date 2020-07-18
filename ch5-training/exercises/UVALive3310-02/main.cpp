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

const int maxn = 100000+5;
const int inf = 1e9;
int n, tot;
int ans;

// == Graph definition ==
vector<int> G[maxn];

class Edge {
public:
    int to, weight, s, t;
    bool loop;
    Edge *next;
    Edge() {}
    Edge(int v, int w, int s, int t, bool loop) : to(v), weight(w), s(s), t(t), loop(loop) {
        next = NULL;
    }
};
vector<Edge> edges;

void add(int x, int y, int w, int s, int t, bool loop) {
    edges.push_back(Edge(y, w, s, t, loop));
    G[x].push_back(edges.size() - 1);
}

int dfn[maxn], low[maxn];
int ins[maxn];
stack<int> stk;
int clk = 0;

void initG() {
    _for(i, 0, maxn) G[i].clear();
    clk = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(ins, 0, sizeof(ins));
    while (stk.size()) stk.pop();
}

bool tarjan(int u) {
    low[u] = dfn[u] = ++clk;
    stk.push(u);
    ins[u] = 1;
    for(int i = 0; i < G[u].size(); i++) {
        const Edge& e = edges[G[u][i]];
        int v = e.to;
        if(!dfn[v]) {
            if(tarjan(v) == false) return false;
            low[u] = min(low[u], low[v]);
        }
        else if(ins[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if(dfn[u] == low[u]) {
        if(u == 0 && stk.size() > 1) return false;
        while (true) {
            int x = stk.top();
            stk.pop();
            ins[x] = false;

            if(x == u) break;
        }
    }

    return true;
}
// == Graph finished ==


// == build graph, important ==
const int maxl = 82;
char buf[maxl];
char Cmd[maxn][maxl];

ll nxt[maxn], len[maxn];
bool Die[maxn], vis[maxn];
int ID[maxn], pos[maxn];

void initbuild() {
    memset(ID, -1, sizeof(ID));
    memset(pos, -1, sizeof(pos));
    memset(Die, 0, sizeof(Die));
    memset(nxt, -1, sizeof(nxt));
    memset(len, 0, sizeof(len));
}

bool judge(const int u, int &v, int &w) {
    memset(vis, 0, sizeof(vis));
    vis[u] = 1;
    bool loop = false;

    while (ID[v] == -1) {
        vis[v] = 1;
        w += len[v];
        v = nxt[v];

        if(vis[v]) {
            loop = true;
            break;
        }
    }
    return loop;
}

void build() {
    initbuild();
    ID[0] = ++tot;
    pos[tot] = 0;

    _for(i, 0, n) {
        if(Cmd[i][0] == 'l') {
            int s = -1, t = -1;
            sscanf(Cmd[i], "%*s%d%d", &s, &t);
            s--;

            if(ID[s] == -1) {
                ID[s] = ++tot;
                pos[tot] = s;
            }
            if(ID[i] == -1) {
                ID[i] = ++tot;
                pos[tot] = i;
            }

            nxt[i] = i;
        }
        else if(Cmd[i][0] == 'i' || Cmd[i][0] == 'j') {
            int v;
            sscanf(Cmd[i], "%*s%d", &v);
            v--;

            if(Cmd[i][0] == 'i' && ID[i] == -1) {
                ID[i] = ++tot;
                pos[tot] = i;
            }

            nxt[i] = v;
        }
        else if(Cmd[i][0] == 'd') {
            if(ID[i] == -1) {
                ID[i] = ++tot;
                pos[tot] = i;
            }
            Die[ID[i]] = true;
            nxt[i] = i;
        }
        else {
            nxt[i] = (i + 1) % n;
        }

        len[i] = nxt[i] == i ? 0 : 1;
    }

    _forDown(i, tot, 1) {
        if(Die[i]) continue;

        int u = pos[i];
        int v = nxt[u];
        int w = len[u];

        bool lp = judge(u, v, w);
        if(lp) {
            add(ID[u], ID[u], inf, -1, -1, false);
            continue;
        }

        len[u] = w;
        nxt[u] = v;
        if(v != u) {
            add(ID[u], ID[v], w, -1, -1, false);
        }
        if(Cmd[u][0] == 'j') continue;

        // then deal with pass, loop, ifgo
        // just one step
        v = (u + 1) % n;
        w = 1;
        lp = judge(u, v, w);
        if(lp) {
            add(ID[u], ID[u], inf, -1, -1, false);
            continue;
        }

        int s = -1, t = -1;
        if(Cmd[u][0] == 'l') {
            sscanf(Cmd[u], "%*s%d%d", &s, &t);
            s--;
        }
        add(ID[u], ID[v], w, ID[s], t, Cmd[u][0] == 'l');
    }
}
// == build finished ==

// == spfa get longest path ==
ll cnt[maxn], D[maxn];
int inq[maxn];

void initspfa() {
    memset(cnt, 0, sizeof(cnt));
    memset(inq, 0, sizeof(inq));
    memset(D, 0, sizeof(D));
}

void spfa() {
    initspfa();

    queue<int> que;
    int st = ID[0];
    inq[st] = 1;
    D[st] = 1;
    que.push(st);

    while (que.size()) {
        int x = que.front();
        que.pop();
        inq[x] = false;

        if(Die[x] && ans < D[x]) ans = D[x];
        for(int i = 0; i < G[x].size(); i++) {
            const Edge& e = edges[G[x][i]];
            int y = e.to;
            int w = e.weight;
            if(e.loop) w += (D[x] - D[e.s] + 1) * (e.t - 1);

            if(D[y] < D[x] + w) {
                D[y] = D[x] + w;
                if(!inq[y]) {
                    inq[y] = true;
                    que.push(y);

                    if(++cnt[y] > tot) {
                        printf("infinity\n");
                        return;
                    }
                }
            }
        }
    }
    if(ans > inf) printf("infinity\n");
    else cout << ans << endl;
}
// == spfa finished ==

// == get cmd ==
void getCmd() {
    _for(i, 0, strlen(buf)) buf[i] = tolower(buf[i]);
    char *p = strtok(buf, " ");
    while (p) {
        strcat(Cmd[n], p);
        strcat(Cmd[n], " ");
        p = strtok(NULL, " ");
    }
    n++;
}

bool cmdModify() {
    bool die = false;
    _for(i, 0, n) {
        if(Cmd[i][0] == 'd') die = true;
        if(Cmd[i][0] == 'i' || Cmd[i][0] == 'j') {
            int v;
            sscanf(Cmd[i], "%*s%d", &v);
            v--;

            if(v == (i + 1) % n) Cmd[i][0] = 'p';
            if(i == v && !die) return false;
        }
    }
    return die;
}
// == get cmd finished ==

void init() {
    memset(Cmd, 0, sizeof(Cmd));
    n = tot = 0;
}

void test() {
    _for(i, 0, n) debug(Cmd[i]);
}

int main() {
    freopen("input.txt", "r", stdin);
    while (fgets(buf, sizeof(buf) / sizeof(buf[0]), stdin)) {
        if(buf[0] == '\n') break;
        init();
        getCmd();

        while (fgets(buf, sizeof(buf) / sizeof(buf[0]), stdin)) {
            if(buf[0] == '\n') break;
            _for(i, 0, strlen(buf)) if(isspace(buf[i])) buf[i] = ' ';
            getCmd();
        }
        // one test case finished
        //test();
        if(!cmdModify()) {
            printf("infinity\n");
            continue;
        }

        // then build graph
        initG();
        build();

        if(!tarjan(1)) {
            printf("infinity\n");
            continue;
        }

        ans = -1;
        spfa();
    }
}