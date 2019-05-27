#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>


using namespace std;
const int maxn = 500 + 10;
const int maxm = 3000;
const int inf = 0x3f3f3f3f;

struct Edge {
    int from, to, dist;
    Edge(int from, int to, int dist) : from(from), to(to), dist(dist) {}
};

struct Bellmanford {
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];

    int d[maxn];
    int prev[maxn];
    int cnt[maxn];
    bool inq[maxn];

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

    bool negaCycle() {
        memset(prev, -inf, sizeof(prev));
        memset(cnt, 0, sizeof(cnt));
        memset(inq, 0, sizeof(inq));

        queue<int> q;
        for(int i = 0; i < n; i++) {
            q.push(i); inq[i] = true; d[i] = 0;
            // find nega cycle, so d[i] = 0
        }

        while(!q.empty()) {
            int u = q.front(); q.pop(); inq[u] = false;

            for(int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(d[e.to] > d[u] + e.dist) {
                    d[e.to] = d[u] + e.dist;
                    prev[e.to] = G[u][i];

                    if(!inq[e.to]){
                        q.push(e.to); inq[e.to] = true; if(++cnt[e.to] > n) return true;
                    }
                }
            }
        }
        return false;
    }
};

int main() {
    int kase, n, m, w;
    scanf("%d", &kase);

    while(kase--) {
        scanf("%d%d%d", &n, &m, &w);
        Bellmanford bell; bell.init(n);

        for(int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            bell.addEdge(a-1, b-1, c);
            bell.addEdge(b-1, a-1, c);
        }

        for(int i = 0; i < w; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            bell.addEdge(a-1, b-1, -c);
        }

        bool flag = bell.negaCycle();
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
}