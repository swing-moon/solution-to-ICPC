#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>

using namespace std;
const int maxn = 100 + 10;
const int inf = 0x3f3f3f3f;

struct Edge {
    int from, to, weight;
};

struct Node {
    int dist, u;
    bool operator < (const Node& rhs) const {
        return dist > rhs.dist;
    }
};

struct Dijkstra {
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];

    bool vis[maxn];
    int d[maxn], pid[maxn];

    void init(int n) {
        this->n = n;
        edges.clear();
        for(int i = 0; i < n; i++) G[i].clear();
    }

    void addEdge(int from, int to, int weight) {
        edges.push_back((Edge){from, to, weight});
        m = edges.size();
        G[from].push_back(m-1);
    }

    void dijkstra(int s) {
        //
        memset(vis, 0, sizeof(vis));
        for(int i = 0; i < n; i++) d[i] = inf;
        d[s] = 0;
        priority_queue<Node> pq;

        pq.push((Node){0, s});
        while(!pq.empty()) {
            Node x = pq.top(); pq.pop();
            int u = x.u;
            if(vis[u]) continue;
            vis[u] = true;

            for(int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(e.weight > 0 && d[e.to] > d[u] + e.weight) {
                    d[e.to] = d[u] + e.weight;
                    pid[e.to] = G[u][i];
                    pq.push((Node){d[e.to], e.to});
                }
            }
        }
    }
};

Dijkstra dij;

int N, M, L;
int used[maxn][maxn][maxn];
// used[src][u][v] means if (u, v) is contained in the shortest path from src

int idx[maxn][maxn];
// idx[][] is for the choosen edge
// may be there are multi edges

int sumTree[maxn];
vector<int> pic[maxn][maxn];

int firstCal() {
    //
    int ans = 0;
    memset(used, 0, sizeof(used));

    for(int src = 0; src < N; src++) {
        sumTree[src] = 0;
        dij.dijkstra(src);
        for(int i = 0; i < N; i++) {
            if(i != src) {
                //
                int pa = dij.edges[dij.pid[i]].from;
                used[src][pa][i] = used[src][i][pa] = 1;
            }
            sumTree[src] += (dij.d[i] == inf ? L : dij.d[i]);
        }


        ans += sumTree[src];
    }
    return ans;
}

int delCal(int u, int v) {
    // deleted (u, v) and rebuid dij-Tree
    int& e1 = dij.edges[idx[u][v]].weight;
    int& e2 = dij.edges[idx[v][u]].weight;

    if(pic[u][v].size() == 1) e1 = e2 = -1;
    else e1 = e2 = pic[u][v][1];

    int ans = 0;
    for(int src = 0; src < N; src++) {
        if(!used[src][u][v]) ans += sumTree[src];
        else {
            // rebuid tree
            dij.dijkstra(src);
            for(int i = 0; i < N; i++) {
                ans += (dij.d[i] == inf ? L : dij.d[i]);
            }
        }
    }

    e1 = e2 = pic[u][v][0];

    return ans;
}

int main() {
    while(scanf("%d%d%d", &N, &M, &L) == 3) {
        dij.init(N);
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++) pic[i][j].clear();

        for(int i = 0; i < M; i++) {
            int u, v, s;
            scanf("%d%d%d", &u, &v, &s); u--; v--;
            pic[u][v].push_back(s);
            pic[v][u].push_back(s);
        }

        // build graph
        for(int i = 0; i < N; i++) {
            for(int j = i+1; j < N; j++) if(!pic[i][j].empty()) {
                sort(pic[i][j].begin(), pic[i][j].end());

                dij.addEdge(i, j, pic[i][j][0]);
                idx[i][j] = dij.m - 1;
                dij.addEdge(j, i, pic[i][j][0]);
                idx[j][i] = dij.m - 1;
            }
        }

        int len1 = firstCal();
        int len2 = -1;
        for(int i = 0; i < N; i++) {
            for(int j = i+1; j < N; j++) if(!pic[i][j].empty()) {
                //
                len2 = max(len2, delCal(i, j));
            }
        }
        printf("%d %d\n", len1, len2);
    }
}