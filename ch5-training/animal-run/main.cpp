#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

const int inf = 0x3f3f3f3f;
const int maxsz = 1000 + 10;
const int maxn = 3000000;

struct Edge {
    int from, to, weight;
};

struct Node {
    int d, u;
    bool operator < (const Node& rhs) const {
        return d > rhs.d;
    }
};

struct Dijkstra {
    int n, m;
    vector<int> G[maxn];
    vector<Edge> edges;

    bool vis[maxn];
    int pid[maxn], d[maxn];

    void init(int n) {
        //
        this->n = n;
        edges.clear();
        for(int i = 0; i < n; i++) G[i].clear();
    }

    void addEdge(int from, int to, int weight) {
        //
        edges.push_back((Edge){from, to, weight});
        m = edges.size();
        G[from].push_back(m-1);
    }

    void dijkstra(int s) {
        //
        for(int i = 0; i < n; i++) d[i] = inf;
        d[s] = 0;
        memset(vis, 0, sizeof(vis));
        priority_queue<Node> pq;

        pq.push((Node){0, s});
        while(!pq.empty()) {
            //
            Node x = pq.top(); pq.pop();
            int u = x.u;

            if(vis[u]) continue;
            vis[u] = true;

            for(int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(d[e.to] > d[u] + e.weight) {
                    d[e.to] = d[u] + e.weight;
                    pid[e.to] = G[u][i];
                    pq.push((Node){d[e.to], e.to});
                }
            }
        }
    }
};


#define REP(i, n) for(int i = 0; i < (n); i++)

int n, m;
int cost[maxsz][maxsz][3];

int ID(int r, int c, int type) {
    return r*m+c+1 + type*n*m;
}

int read() {
    int x; scanf("%d", &x); return x;
}

// 0 is level, 1 is vertical, 2 is slash

Dijkstra dij;

void triangleEdge(int* e1, int* e2, int* e3) {
    int* edges[3] = {e1, e2, e3};
    // edges[i] = e1 = {i, j, up}

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) if(i != j) {
            int id1 = ID(edges[i][0], edges[i][1], edges[i][2]);
            int id2 = ID(edges[j][0], edges[j][1], edges[j][2]);
            int w = cost[edges[j][0]][edges[j][1]][edges[j][2]];

            dij.addEdge(id1, id2, w);
        }
    }
}

int main() {
    int kase = 0;
    while(scanf("%d%d", &n, &m) == 2 && n) {
        REP(i, n) REP(j, m-1) cost[i][j][0] = read();
        REP(i, n-1) REP(j, m) cost[i][j][1] = read();
        REP(i, n-1) REP(j, m-1) cost[i][j][2] = read();

        dij.init(n*m*3 + 2);

        // check each slash
        REP(i, n-1) REP(j, m-1) {
            int top[] = {i, j, 0};
            int bottom[] = {i+1, j, 0};
            int left[] = {i, j, 1};
            int right[] = {i, j+1, 1};
            int slash[] = {i, j, 2};

            triangleEdge(top, right, slash);
            triangleEdge(bottom, left, slash);
        }

        // add start edge and end edge
        REP(i, n-1) dij.addEdge(0, ID(i, 0, 1), cost[i][0][1]);
        REP(i, m-1) dij.addEdge(0, ID(n-1, i, 0), cost[n-1][i][0]);

        dij.dijkstra(0);

        int ans = inf;
        REP(i, n-1) ans = min(ans, dij.d[ID(i, m-1, 1)]);
        REP(i, m-1) ans = min(ans, dij.d[ID(0, i, 0)]);

        printf("Case %d: Minimum = %d\n", ++kase, ans);
    }
}