#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
//typedef long long llong;
const int maxn = 1000 + 10;
const int inf = 0x3f3f3f3f;

/*
 *  first we find min cost
 *      then we augment
 */

struct Edge {
    int from, to, cap, flow, cost;
    Edge(int from, int to, int cap, int flow, int cost) : from(from), to(to), cap(cap), flow(flow), cost(cost) {}
};


/*
 *  core algorithms:
 *    for i = 0 to G[u].size()    e = edges[G[u][i]]
 *      if(e.cap > e.flow && e.cost + d[u] < d[e.to])
 *          update: aug[e.to] = f(aug[u]); d[e.to] = f(d[u])
 *          if(!inq[e.to]) { Q.push(e.to); inq[e.to] = 1; }
 */

struct MCMF {
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];

    int inq[maxn];
    int d[maxn];
    int aug[maxn];
    int pre[maxn];
    int cnt[maxn];

    void init(int n) {
        this->n = n + 3;
        edges.clear();
        for(int i = 0; i < n; i++) G[i].clear();
    }

    void addEdge(int from, int to, int cap, int cost) {
        edges.push_back(Edge(from, to, cap, 0, cost));
        edges.push_back(Edge(to, from, 0, 0, -cost));
        m = edges.size();

        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    // assure there are no nega-cycle
    bool BellmanFord(int s, int t, int& flow, int& cost) {
        for(int i = 0; i < n; i++) d[i] = inf;
        memset(inq, 0, sizeof(inq));
        memset(cnt, 0, sizeof(cnt));

        queue<int> q;
        inq[s] = 1; d[s] = 0; aug[s] = inf; pre[s] = 0;
        q.push(s);

        while(!q.empty()) {
            //
            int u = q.front(); inq[u] = 0; q.pop();
            for(int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(e.cap > e.flow && e.cost + d[u] < d[e.to]) {
                    //update
                    aug[e.to] = min(aug[u], e.cap-e.flow);
                    // made a mistake here!
                    pre[e.to] = G[u][i];
                    d[e.to] = d[u] + e.cost;

                    if(!inq[e.to]) { q.push(e.to); inq[e.to] = 1; if(++cnt[e.to] > n) return false; }
                    // judge nega-cycle
                }
            }
        }

        if(d[t] == inf) return false;
        flow += aug[t];
        cost += d[t] * aug[t];

        for(int u = t; u != s; u = edges[pre[u]].from) {
            edges[pre[u]].flow += aug[t];
            edges[pre[u]^1].flow -= aug[t];
        }

        return true;
    }

    int mincostMaxflow(int s, int t) {
        int flow = 0, cost = 0;
        while(BellmanFord(s, t, flow, cost));
        return cost;
    }
};


int main() {
    int n, m;
    cin >> n >> m;
    MCMF mcmf;
    mcmf.init(n);

    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        mcmf.addEdge(a-1, b-1, 1, c);
        mcmf.addEdge(b-1, a-1, 1, c);
    }

    int s = n;
    int t = s + 1;
    mcmf.addEdge(s, 0, 2, 0);
    mcmf.addEdge(n-1, t, 2, 0);
    int res = mcmf.mincostMaxflow(s, t);
    cout << res << endl;
}