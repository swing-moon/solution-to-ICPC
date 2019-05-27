#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <cmath>

using namespace std;
const int maxn = 55 + 10;
typedef long long llong;
const llong inf = 1LL << 60;


char format(int u) {
    return u < 26 ? 'A' + u : 'a' + (u - 26);
}

struct Edge {
    int from, to, upper;
    Edge(int f, int t, int u) : from(f), to(t), upper(u) {}
};

struct Node {
    llong dist;
    int u;
    Node(llong d, int u) : dist(d), u(u) {}

    bool operator < (const Node& rhs) const {
        return dist > rhs.dist;
    }
};

struct Dijkstra {
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];

    bool vis[maxn];
    llong d[maxn];
    int pid[maxn];

    void init() {
        for(int i = 0; i < maxn; i++) G[i].clear();
        edges.clear();
    }

    void addEdge(int from, int to, int kind) {
        edges.push_back(Edge(from, to, kind));
        m = edges.size();
        G[from].push_back(m-1);
        // cout << "suc!" << endl;
    }

    void dijkstra(llong item, int s) {
        priority_queue<Node> pq;
        for(int i = 0; i < maxn; i++) d[i] = inf;
        memset(pid, 0, sizeof(pid));

        d[s] = item; pid[s] = -1;
        memset(vis, 0, sizeof(vis));
        pq.push(Node(item, s));

        //
        while(!pq.empty()) {
            //
            Node x = pq.top(); pq.pop();
            int u = x.u;
            if(vis[u]) continue;
            vis[u] = true;

            for(int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                //
                llong flow;
                if(e.upper) flow = (llong)ceil(d[u] * 1.0 / 19 * 20);
                else flow = d[u] + 1;
                // cout << "flow " << flow << " " << endl;

                if(d[e.to] > flow || (d[e.to] == flow && /*dicitonary order min*/
                    format(u) < format(edges[pid[e.to]].from))) {
                    d[e.to] = flow;

                    pid[e.to] = G[u][i];
                    pq.push(Node(d[e.to], e.to));
                }
            }
        }
    }

    void outPrint(int s) {
        if(pid[s] == -1) {
            printf("%c\n", format(s));
            return;;
        }
        printf("%c-", format(s));
        outPrint(edges[pid[s]].from);
    }
};

int n, p;
int src, dest;
Dijkstra dij;

int read_node() {
    char ch[9];
    scanf("%s", ch);
    if(ch[0] >= 'A' && ch[0] <= 'Z') return ch[0] - 'A';
    else return ch[0] - 'a' + 26;
}

int isUpper(int u) {
    return u < 26 ? 1 : 0;
}


int main() {
    int kase = 0;
    while(scanf("%d", &n) == 1 && n >= 0) {
        dij.init();

        for(int i = 0; i < n; i++) {
            int u = read_node();
            int v = read_node();

            if(u != v) {
                dij.addEdge(u, v, isUpper(u));
                dij.addEdge(v, u, isUpper(v));
            }
        }

        scanf("%d", &p);
        src = read_node();
        dest = read_node();
        // cout << src << dest << endl;

        printf("Case %d:\n", ++kase);
        dij.dijkstra(p, dest);
        printf("%lld\n", dij.d[src]);
        dij.outPrint(src);
    }
}