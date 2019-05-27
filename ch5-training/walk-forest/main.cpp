#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 1000 + 10;

struct Edge {
    int from, to, weight;
    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
};

struct Node {
    int dist, u;
    Node(int d, int u) : dist(d), u(u) {}

    bool operator < (const Node& rhs) const {
        return dist > rhs.dist;
    }
};

struct Dijkstra {
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];
    bool vis[maxn];
    int pid[maxn]; int d[maxn];

    void init(int n) {
        this->n = n;
        edges.clear();
        for(int i = 0; i < n; i++) G[i].clear();
    }

    void addEdge(int from, int to, int dist) {
        edges.push_back(Edge(from, to, dist));
        m = edges.size();
        G[from].push_back(m-1);
    }

    void dijkstra(int s) {
        //
        priority_queue<Node> pq;
        memset(vis, 0, sizeof(vis));
        for(int i = 0; i < n; i++) d[i] = inf;
        d[s] = 0;

        pq.push(Node(0, s));
        while(!pq.empty()) {
            Node x = pq.top(); pq.pop();
            int u = x.u;
            if(vis[u]) continue;
            vis[u] = true;

            for(int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(d[e.to] > d[u] + e.weight) {
                    d[e.to] = d[u] + e.weight;
                    pid[e.to] = G[u][i];
                    pq.push(Node(d[e.to], e.to));
                }
            }
        }
    }
};


Dijkstra dij;
int cnt[maxn];

int count(int u) {
    if(u == 1) return 1;
    int& ans = cnt[u];
    if(ans >= 0) return ans;

    ans = 0;
    for(int i = 0; i < dij.G[u].size(); i++) {
        int v = dij.edges[dij.G[u][i]].to;
        if(dij.d[v] < dij.d[u]) ans += count(v);
    }
    return ans;
}

int main() {
    int n, m;
    while(scanf("%d%d", &n, &m) == 2) {
        dij.init(n);
        for(int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c); a--; b--;
            dij.addEdge(a, b, c);
            dij.addEdge(b, a, c);
        }

        dij.dijkstra(1);
        // from home, d[] means node to home!
        memset(cnt, -1, sizeof(cnt));
        printf("%d\n", count(0));
    }
}