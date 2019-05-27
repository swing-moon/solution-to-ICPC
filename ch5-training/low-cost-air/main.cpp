#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 4000 + 10;
const int maxt = 100 + 10;

//
struct Edge {
    int from, to, weight, flag;
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
    int d[maxn], pid[maxn];

    void init(int n) {
        //
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void addEdge(int from, int to, int weight, int flag) {
        //
        edges.push_back((Edge) {from, to, weight, flag});
        m = edges.size();
        G[from].push_back(m-1);
    }

    void dijkstra(int s) {
        //
        priority_queue<Node> pq;
        for(int i = 0; i < n; i++) d[i] = inf;
        d[s] = 0;
        memset(vis, 0, sizeof(vis));

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
                    pq.push((Node){d[e.to], e.to});
                }
            }
        }
    }

    vector<int> getPath(int s, int t) {
        vector<int> path;
        while(t != s) {
            path.push_back(edges[pid[t]].flag);
            t = edges[pid[t]].from;
        }
        reverse(path.begin(), path.end());
        return path;
    }
};


#include <map>
map<int, int> city_id;
int ncities;
vector<int> ticks[maxt], iti;
int cost[maxt];


int read() {
    int x; scanf("%d", &x); return x;
}


int ID(int city) {
    //
    if(city_id.count(city)) return city_id[city];
    city_id[city] = ncities++;
    return ncities - 1;
}

int myhash(int curid, int walk) {
    return (walk - 1) * ncities + curid;
}

Dijkstra dij;

int main() {
    int NT, NI, x, kase = 0;
    int lent, leniti;
    while(scanf("%d", &NT) == 1 && NT) {
        //
        ncities = 0;
        city_id.clear();
        for(int i = 0; i < NT; i++) {
            ticks[i].clear();
            scanf("%d%d", &cost[i], &lent);
            while(lent--) {
                x = read(); ticks[i].push_back(ID(x));
            }
        }

        scanf("%d", &NI);
        kase++;

        for(int trip = 1; trip <= NI; trip++) {
            // start trip

            iti.clear();
            scanf("%d", &leniti);
            for(int k = 0; k < leniti; k++) {
                x = read(); iti.push_back(ID(x));
            }

            dij.init(ncities * leniti);

            for(int ti = 0; ti < NT; ti++) {
                for(int walk = 1; walk < leniti; walk++) {
                    int beg = ticks[ti][0];
                    int next = walk;

                    for(int leg = 1; leg < ticks[ti].size(); leg++) {
                        if(ticks[ti][leg] == iti[next]) next++;
                        dij.addEdge(myhash(beg, walk), myhash(ticks[ti][leg], next), cost[ti], ti+1);

                        if(next == leniti) break;
                    }
                }
            }

            int src = myhash(iti[0], 1), dest = myhash(iti[leniti-1], leniti);
            dij.dijkstra(src);
            printf("Case %d, Trip %d: Cost = %d\n", kase, trip, dij.d[dest]);
            printf("  Tickets used:");

            vector<int> path = dij.getPath(src, dest);
            for(int i = 0; i < path.size(); i++) printf(" %d", path[i]);
            printf("\n");
        }
        // end one trip
    }
}