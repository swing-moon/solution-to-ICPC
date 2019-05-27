#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 80000 + 10;

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
    vector<Edge> edges;
    vector<int> G[maxn];

    bool vis[maxn];
    int pid[maxn], d[maxn];

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
        for(int i = 0; i < n; i++) d[i] = inf;
        memset(vis, 0, sizeof(vis));
        priority_queue<Node> pq;

        d[s] = 0; pq.push((Node){0, s});
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
                    pq.push((Node){d[e.to], e.to});
                }
            }
        }
    }
};

// complement:
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, -1, 0, 1};
const int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3;
const int inv[] = {2, 3, 0, 1};
const int maxr = 100;
const int maxc = 100;

int cost[maxr][maxc][4];
int id[maxr][maxc][4][2];
int n;

int getid(int r, int c, int dir, int flag) {
    int& x = id[r][c][dir][flag];
    if(x == 0) x = ++n;
    return x;
}

int read() {
    int x; scanf("%d", &x); return x;
}

int R, C;

bool valid(int r, int c, int dir) {
    if(r < 0 || c < 0 || r >= R || c >= C) return false;
    return cost[r][c][dir] > 0;
}

Dijkstra dij;

int main() {
    int r1, c1, r2, c2, kase = 0;
    while(scanf("%d%d%d%d%d%d", &R, &C, &r1, &c1, &r2, &c2) == 6 && R) {
        r1--; c1--; r2--; c2--;
        for(int r = 0; r < R; r++) {
            for(int c = 0; c < C-1; c++) cost[r][c][RIGHT] = cost[r][c+1][LEFT] = read();
            if(r != R-1) for(int c = 0; c < C; c++) cost[r][c][DOWN] = cost[r+1][c][UP] = read();
        }

        dij.init(R*C*8+1);

        n = 0;
        memset(id, 0, sizeof(id));

        // Red-Green Light algorithm
        // build status graph

        for(int dir = 0; dir < 4; dir++) if(valid(r1, c1, dir)) {
            dij.addEdge(0, getid(r1+dr[dir], c1+dc[dir], dir, 1), cost[r1][c1][dir]*2);
        }
        // start from 0

        for(int r = 0; r < R; r++) for(int c = 0; c < C; c++) {
            for(int dir = 0; dir < 4; dir++) if(valid(r, c, inv[dir])) {
                for(int ndir = 0; ndir < 4; ndir++) if(valid(r, c, ndir)) {
                    for(int flag = 0; flag < 2; flag++) {
                        int nr = r+dr[ndir], nc = c+dc[ndir];
                        // I made a bug here
                        // nr = r+dr[ndir] not r+dr[dir]

                        int ncost = cost[r][c][ndir], nflag = 0;

                        if(dir != ndir) {
                            // need to doubled!
                            if(!flag) ncost += cost[r][c][inv[dir]];
                            ncost += cost[r][c][ndir]; nflag = 1;
                        }
                        dij.addEdge(getid(r, c, dir, flag), getid(nr, nc, ndir, nflag), ncost);
                    }
                    // end of flag loop
                }
            }
        }

        // build-finished!
        dij.dijkstra(0);

        int ans = inf;
        for(int dir = 0; dir < 4; dir++) if(valid(r2, c2, inv[dir])) {
            for(int flag = 0; flag < 2; flag++) {
                int v = dij.d[getid(r2, c2, dir, flag)];
                // cout << getid(r2, c2, dir, flag) << endl;

                /*
                cout << "v " << v << endl;
                cout << "cost" << cost[r2][c2][inv[dir]] << endl;
                cout << "test " << dij.d[50] << endl;

                cout << "test: " << endl;
                for(int i = 0; i < dij.n-1; i++)
                    cout << dij.d[i] << " ";
                cout << endl;
                */

                if(!flag) v += cost[r2][c2][inv[dir]];
                ans = min(ans, v);
            }
        }

        printf("Case %d: ", ++kase);
        if(ans == inf) printf("Impossible\n"); else printf("%d\n", ans);
    }
}