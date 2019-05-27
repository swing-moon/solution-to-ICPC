#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 200 + 5;
const int maxm = 200 + 5;
const int inf = 0x3f3f3f3f;

struct Edge {
    int from, to, cap, flow;
    Edge(int from, int to, int cap, int flow) : from(from), to(to), cap(cap), flow(flow) {}
};

struct EdmondsKarp {
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];
    // G[i][j] means the id of edges

    int res[maxn];
    int pre[maxn];

    void init(int n) {
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void addEdge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        int m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    int maxFlow(int s, int t) {
        int flow = 0;

        // loop for augment
        for(;;) {
            memset(res, 0, sizeof(res));

            // try to find maxflow , result in res[t]
            queue<int>q; q.push(s);

            // because each flow of the edge must be the same
            // loop to find min flow in each edge
            res[s] = inf;
            while(!q.empty()) {
                int u = q.front(); q.pop();
                for(int i = 0; i < G[u].size(); i++) {
                    // G[u][i] is the edge id
                    Edge& e = edges[G[u][i]];

                    if(!res[e.to] && e.flow < e.cap) {
                        pre[e.to] = G[u][i];
                        res[e.to] = min(res[u], e.cap-e.flow);
                        q.push(e.to);
                    }
                }

                // q.push(e.to) remember
                // maxflow problem, we find res[t], break;
                if(res[t]) break;
            }

            if(!res[t]) break;

            // update flow

            for(int u = t; u != s; u = edges[pre[u]].from) {
                //
                edges[pre[u]].flow += res[t];
                edges[pre[u]^1].flow -= res[t];
            }

            flow += res[t];
        }
        return flow;
    }
};

int main() {
    int m, n;
    while(scanf("%d%d", &m, &n) != EOF) {
        EdmondsKarp ek;
        ek.init(n);
        for(int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            ek.addEdge(a-1, b-1, c);
        }

        cout << ek.maxFlow(0, n-1) << endl;
    }
}