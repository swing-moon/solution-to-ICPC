#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

using namespace std;
const int maxn = 1000 + 10;
const int inf = 0x3f3f3f3f;

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
        this-> n = n;
        edges.clear();
        for(int i = 0; i < n; i++) G[i].clear();
    }

    void addEdge(int from, int to, int weight) {
        edges.push_back(Edge(from, to, weight));
        m = edges.size();
        G[from].push_back(m-1);
    }

    void dijkstra(int s) {
        // init:
        priority_queue<Node> pq;
        for(int i = 0; i < n; i++) d[i] = inf;
        memset(vis, 0, sizeof(vis));
        d[s] = 0;

        pq.push((Node){0, s});
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

    void outPath(int s, int* dist, vector<int>* path) {
        dijkstra(s);
        for(int i = 0; i < n; i++) {
            // get dist:
            dist[i] = d[i];

            // get path:
            path[i].clear();
            int t = i;
            path[i].push_back(t);
            while(t != s) {
                path[i].push_back(edges[pid[t]].from);
                t = edges[pid[t]].from;
            }
            reverse(path[i].begin(), path[i].end());
        }
    }
};

// solve problem:
// enum midStation
Dijkstra dij;
int d1[maxn], d2[maxn];
vector<int> path1[maxn], path2[maxn];

int main() {
    int kase = 0, N, M, S, E, X, Y, Z, K;
    while(scanf("%d%d%d", &N, &S, &E) == 3) {
        scanf("%d", &M);
        S--; E--;
        dij.init(N);

        for(int i = 0; i < M; i++) {
            scanf("%d%d%d", &X, &Y, &Z); X--; Y--;
            dij.addEdge(X, Y, Z);
            dij.addEdge(Y, X, Z);
        }

        dij.outPath(S, d1, path1);
        dij.outPath(E, d2, path2);
        // remember reverse path2

        int ans = d1[E];
        vector<int> path = path1[E];
        int midStat = -1;

        scanf("%d", &K);
        for(int i = 0; i < K; i++) {
            scanf("%d%d%d", &X, &Y, &Z); X--; Y--;
            // enum each i as the midStat

            for(int cnt = 0; cnt < 2; cnt++) {
                if(d1[X] + d2[Y] + Z < ans) {
                    ans = d1[X] + d2[Y] + Z;
                    path = path1[X];
                    for(int j = path2[Y].size()-1; j >= 0; j--) {
                        path.push_back(path2[Y][j]);
                    }
                    midStat = X;
                }
                swap(X, Y);
            }
        }

        if(kase != 0) printf("\n");
        kase++;

        for(int i = 0; i < path.size()-1; i++) printf("%d ", path[i]+1);
        printf("%d\n", E+1);
        if(midStat == -1) printf("Ticket Not Used\n");
        else printf("%d\n", midStat+1);

        printf("%d\n", ans);
    }
    return 0;
}