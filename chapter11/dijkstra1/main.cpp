#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 100 + 10;
const int maxm = 10000 + 10;
const int inf = 0x3f3f3f3f;

struct Edge {
    int from, to, dist;
    Edge(int from, int to, int dist) : from(from), to(to), dist(dist) {}
};

struct Node {
    int d, uid;
    Node(int d, int uid) : d(d), uid(uid) {}

    bool operator < (const Node& rhs) const {
        return d > rhs.d;
    }
};

struct Dijkstra {
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn]; // G[u][i] is the id of edges

    bool mark[maxn];
    int d[maxn];
    int prev[maxn];

    void init(int n) {
        this->n = n;
        edges.clear();
        for(int i = 0; i < maxn; i++) G[i].clear();
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
                // e.from == u

                if(d[e.to] > d[u] + e.dist) {
                    d[e.to] = d[u] + e.dist;
                    prev[e.to] = G[u][i];
                    pq.push(Node(d[e.to], e.to));
                }
            }
        }
    }

    void print(int dest, int s) {
        vector<int> path;
        for( ; prev[dest] != -1 ; dest = edges[prev[dest]].from) {
            // cout << dest+1 << "->" << edges[prev[dest]].from+1 << " ";
            path.push_back(dest+1);
        }
        path.push_back(s+1);
        reverse(path.begin(), path.end());

        for(int i = 0; i < path.size()-1; i++)
            cout << path[i] << "->";
        cout << path[path.size()-1] << endl;
    }
};

int main() {
    int n, m;

    while(scanf("%d%d", &n, &m) == 2 && n) {
        Dijkstra dij;
        dij.init(n);

        for(int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            dij.addEdge(a-1, b-1, c);
            dij.addEdge(b-1, a-1, c);
        }

        dij.dijkstra(0);
        cout << dij.d[n-1] << endl;
        dij.print(n-1, 0);
    }
}