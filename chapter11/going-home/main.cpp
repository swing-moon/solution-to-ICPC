#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <cmath>

#define long long llong

using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 10000 + 10;
const int maxm = 1000100;
char grid[105][105];

struct Edge {
    int from, to, flow, cap, cost;
};

struct MCMF {
    int n, m, s, t;
    vector<int> G[maxn];
    vector<Edge> edges;

    // notes: G[i] means the id of edges (from nodes i)

    int inq[maxn];
    int d[maxn];
    int prev[maxn];
    int aug[maxn];

    void init(int n) {
        this->n = n;
        edges.clear();
        for(int i = 0; i < n; i++) G[i].clear();
    }

    void addEdge(int from, int to, int cap, int cost) {
        edges.push_back( (Edge){from, to, 0, cap, cost} );
        edges.push_back( (Edge){to, from, 0, 0, -cost} );
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool bellmanFord(int s, int t, int& flow, int& cost) {
        for(int i = 0; i < n; i++) d[i] = inf;
        memset(inq, 0, sizeof(inq));
        d[s] = 0; prev[s] = 0; inq[s] = 1; aug[s] = inf;

        queue<int> Q; Q.push(s);

        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            inq[u] = 0;

            for(int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];

                if(e.flow < e.cap && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    prev[e.to] = G[u][i];
                    aug[e.to] = min(aug[u], e.cap - e.flow);
                    if(!inq[e.to]) { Q.push(e.to); inq[e.to] = 1; }
                }
            }
        }

        if(d[t] == inf) return false;

        flow += aug[t];
        cost += d[t] * aug[t];

        for(int u = t; u != s; u = edges[prev[u]].from) {
            edges[prev[u]].flow += aug[t];
            edges[prev[u]^1].flow -= aug[t];
        }
        return true;
    }

    int minCost(int s, int t) {
        int flow = 0, cost = 0;
        while(bellmanFord(s, t, flow, cost));
        return cost;
    }
};

struct Point {
    int x, y;
};

int main() {
    int n, m;
    while(scanf("%d%d", &n, &m) == 2 && n) {
        Point H[105], P[105];
        MCMF mcmf;
        int h = 0, p = 0;

        for(int i = 0; i < n; i++) {
            scanf("%s", grid[i]);
            for(int j = 0; j < m; j++) {
                if(grid[i][j] == 'H') { H[h].x = i; H[h].y = j; h++; }
                else if(grid[i][j] == 'm') { P[p].x = i; P[p].y = j; p++; }
            }
        }

        mcmf.init(h+p+1+1);
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < p; j++) {
                int c = fabs(H[i].x - P[j].x) + fabs(H[i].y - P[j].y);
                mcmf.addEdge(i+1, h+1+j, 1, c);
            }
        }

        for(int i = 0; i < h; i++) mcmf.addEdge(0, i+1, 1, 0);
        for(int i = 0; i < p; i++) mcmf.addEdge(h+i+1, h+p+1, 1, 0);

        printf("%d\n", mcmf.minCost(0, h+p+1));
    }
}