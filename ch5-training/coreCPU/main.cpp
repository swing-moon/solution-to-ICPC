#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <queue>

using namespace std;

const int maxn = 20000 + 10;
const int inf = 0x3f3f3f3f;

struct Edge {
    int from, to, flow, cap;
};

struct ISAP {
    int n, m, s, t;
    vector<int> G[maxn];
    vector<Edge> edges;

    bool vis[maxn];
    int d[maxn], cur[maxn];
    int p[maxn], num[maxn];

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

    void bfs() {
        memset(vis, 0, sizeof(vis));
        memset(d, 0, sizeof(d));

        queue<int> Q;
        Q.push(t); d[t] = 0; vis[t] = 1;

        while(!Q.empty()) {
            int x = Q.front(); Q.pop();
            for(int i = 0; i < G[x].size(); i++) {
                Edge& e = edges[G[x][i]];
                if(!vis[e.from] && e.cap > e.flow) {
                    vis[e.from] = 1;
                    d[e.from] = d[x] + 1;
                    Q.push(e.from);
                }
            }
        }
    }

    int augment() {
        int x = t, aug = inf;
        while(x != s) {
            Edge& e = edges[p[x]];
            // p[x] is assigned in maxflow()
            aug = min(aug, e.cap-e.flow);
            x = edges[p[x]].from;
        }

        x = t;
        while(x != s) {
            edges[p[x]].flow += aug;
            edges[p[x]^1].flow -= aug;
            x = edges[p[x]].from;
        }

        return aug;
    }

    int maxFlow() {
        int flow = 0;
        bfs();
        memset(num, 0, sizeof(num));
        for(int i = 0; i < n; i++) num[d[i]]++;

        memset(cur, 0, sizeof(cur));
        int x = s;
        while(d[s] < n) {
            if(x == t) {
                flow += augment(); x = s;
            }

            int ok = 0;
            for(int i = cur[x]; i < G[x].size(); i++) {
                Edge& e = edges[G[x][i]];
                if(e.cap > e.flow && d[x] == d[e.to] + 1) {
                    ok = 1;

                    // assign p[], cur[]
                    p[e.to] = G[x][i];
                    cur[x] = i;
                    x = e.to;

                    break;
                }
            }

            if(!ok) {
                int dist = n-1;
                for(int i = 0; i < G[x].size(); i++) {
                    Edge& e = edges[G[x][i]];
                    if(e.cap > e.flow) dist = min(dist, d[e.to]);
                }

                if(--num[d[x]] == 0) break;
                num[d[x] = dist+1]++;

                cur[x] = 0;
                if(x != s) x = edges[p[x]].from;
            }
        }

        return flow;
    }
};

int main() {
    ISAP isap;
    int n, m;

    while(cin >> n >> m) {
        int s = 0, t = n+1;
        isap.init(t+1, s, t);

        int a, b;
        for(int i = 1; i <= n; i++) {
            scanf("%d%d", &a, &b);
            isap.addEdge(i, t, a);
            isap.addEdge(s, i, b);
        }

        int ui, vi, wi;
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &ui, &vi, &wi);
            isap.addEdge(ui, vi, wi);
            isap.addEdge(vi, ui, wi);
        }

        printf("%d\n", isap.maxFlow());
    }
}