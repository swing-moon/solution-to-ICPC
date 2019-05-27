#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 1000 + 10;
const int maxm = 2000 + 10;
const int inf = 0x3f3f3f3f;

struct Edge {
    int from, to, dist;
    Edge(int from, int to, int dist) : from(from), to(to), dist(dist) {}
};

struct Node {
    int far, uid;
    Node(int far, int uid) : far(far), uid(uid) {}

    bool operator < (const Node& rhs) const {
        return far > rhs.far;
    }
};

struct Dijkstra {
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];
    // G[u][i] means edge id

    int d[maxn];
    int prev[maxn];
    bool mark[maxn];

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
        for(int i = 0; i < n; i++) d[i] = inf;
        d[s] = 0;
        memset(mark, 0, sizeof(mark));
        memset(prev, -1, sizeof(prev));

        priority_queue<Node> pq;
        pq.push(Node(0, s));

        while(!pq.empty()) {
            Node x = pq.top(); pq.pop();
            int u = x.uid;

            if(mark[u]) continue;
            mark[u] = 1;

            for(int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(d[e.to] > d[u] + e.dist) {
                    d[e.to] = d[u] + e.dist;
                    prev[e.to] = G[u][i];
                    pq.push(Node(d[e.to], e.to));
                }
            }
        }
    }
};

int main() {
    int m, n;
    scanf("%d%d", &m, &n);

    Dijkstra dij;
    dij.init(n);
    for(int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        dij.addEdge(a-1, b-1, c);
        dij.addEdge(b-1, a-1, c);
    }

    dij.dijkstra(0);
    printf("%d", dij.d[n-1]);
}