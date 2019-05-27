#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <cctype>

using namespace std;

const int maxn = 500 + 10;
const int inf = 0x3f3f3f3f;

struct Edge {
    int from, to, flow, cap;
};

struct Dinic {
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[maxn];

    bool vis[maxn];
    int cur[maxn];
    int d[maxn];

    void init(int n, int s, int t) {
        this->n = n; this->s = s; this->t = t;
        for(int i = 0; i <= n; i++) G[i].clear();
        edges.clear();
    }

    void addEdge(int from, int to, int cap) {
        edges.push_back( (Edge){from, to, 0, cap} );
        edges.push_back( (Edge){to, from, 0, 0} );
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool bfs() {
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        Q.push(s); d[s] = 0; vis[s] = 1;

        while(!Q.empty()) {
            int x = Q.front(); Q.pop();
            for(int i = 0; i < G[x].size(); i++) {
                Edge& e = edges[G[x][i]];
                if(!vis[e.to] && e.flow < e.cap) {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }

        return vis[t];
    }

    int dfs(int x, int aug) {
        if(x == t || aug == 0) return aug;
        int flow = 0, f;

        for(int& i = cur[x]; i < G[x].size(); i++) {
            Edge& e = edges[G[x][i]];
            if(d[x] + 1 == d[e.to] && (f = dfs(e.to, min(aug, e.cap-e.flow))) > 0 ) {
                e.flow += f;
                edges[G[x][i]^1].flow -= f;

                flow += f;
                aug -= f;

                if(aug == 0) break;
            }
        }
        return flow;
    }

    int maxFlow() {
        int flow = 0;
        while(bfs()) {
            memset(cur, 0, sizeof(cur));
            flow += dfs(s, inf);
        }
        return flow;
    }
};

int N, F, D, Fi, Di, fod, drk;
int s, t;
Dinic dc;

int main() {
    scanf("%d%d%d", &N, &F, &D);
    s = 0; t = F + 2*N + D + 1;
    dc.init(t+1, 0, t);

    for(int i = 1; i <= F; i++) dc.addEdge(0, i, 1);
    for(int i = 1; i <= N; i++) dc.addEdge(F+i, F+i+N, 1);
    for(int i = 1; i <= D; i++) dc.addEdge(F+2*N+i, t, 1);

    for(int i = 1; i <= N; i++) {
        scanf("%d%d", &Fi, &Di);
        for(int j = 0; j < Fi; j++) {
            scanf("%d", &fod);
            dc.addEdge(fod, F+i, 1);
        }
        for(int j = 0; j < Di; j++) {
            scanf("%d", &drk);
            dc.addEdge(F+N+i, F+2*N+drk, 1);
        }
    }
    cout << dc.maxFlow() << endl;
}