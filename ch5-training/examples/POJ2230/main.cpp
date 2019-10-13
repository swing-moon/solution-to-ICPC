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

const int maxn = 100000 + 10;
int n, m;
int st;
vector<int> G[maxn];
int head[maxn];
stack<int> stk;
vector<int> ans;

struct Edge {
    int u, v;
    Edge(int u = 0, int v = 0) : u(u), v(v) {}
};

vector<Edge> edges;

void init() {
    _for(i, 0, maxn) G[i].clear();
    while(!stk.empty()) stk.pop();
    edges.push_back(Edge());
    edges.push_back(Edge());
    Set(head, 0);
    ans.clear();
}

void addEdge(int u, int v) {
    edges.push_back(Edge(u, v));
    G[u].push_back(edges.size() - 1);
}

void euler() {
    stk.push(st);
    while (!stk.empty()) {
        int x = stk.top(), i = head[x];
        // debug(x);

        if(i < G[x].size()) {
            int eid = G[x][i];
            int y = edges[eid].v;

            stk.push(y);
            head[x] = i + 1;
        }
        else {
            stk.pop();
            ans.push_back(x);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> m;

    _rep(i, 1, m) {
        int x, y;
        scanf("%d%d", &x, &y);
        addEdge(x, y);
        addEdge(y, x);
    }

    st = 1;
    euler();
    for(int i = ans.size() - 1; i >= 0; i--) printf("%d\n", ans[i]);
}