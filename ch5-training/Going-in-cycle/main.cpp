#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <stack>
#include <cstdlib>

using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 1000;

struct Edge {
    int from, to;
    double weight;
};

// find negaCycle, let all nodes in the queue

struct Bellman {
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];

    bool inq[maxn];
    double d[maxn];
    int pid[maxn], cnt[maxn];

    void init(int n) {
        this->n = n;
        edges.clear();
        for(int i = 0; i < n; i++) G[i].clear();
    }

    void addEdge(int from, int to, double w) {
        edges.push_back((Edge){from, to, w});
        m = edges.size();
        G[from].push_back(m-1);
    }

    bool negaCycle() {
        memset(inq, 0, sizeof(inq));
        memset(cnt, 0, sizeof(cnt));
        queue<int> q;
        for(int i = 0; i < n; i++) {
            d[i] = 0; inq[0] = true; q.push(i);
        }

        while(!q.empty()) {
            int x = q.front(); q.pop(); inq[x] = false;

            for(int i = 0; i < G[x].size(); i++) {
                Edge& e = edges[G[x][i]];
                if(d[e.to] > d[x] + e.weight) {
                    d[e.to] = d[x] + e.weight;
                    pid[e.to] = G[x][i];

                    if(!inq[e.to]) {
                        q.push(e.to); inq[e.to] = true;
                        if(++cnt[e.to] > n) return true;
                    }
                }
            }
        }

        return false;
    }
};

Bellman bell;

bool test(double x) {
    for(int i = 0; i < bell.m; i++)
        bell.edges[i].weight -= x;
    bool ret = bell.negaCycle();

    for(int i = 0; i < bell.m; i++) bell.edges[i].weight += x;
    return ret;
}


int main() {
    int T;
    scanf("%d", &T);

    for(int kase = 1; kase <= T; kase++) {
        int n, m;
        scanf("%d%d", &n, &m);
        bell.init(n);

        int maxv = 0;
        while(m--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w); u--; v--; maxv = max(maxv, w);
            bell.addEdge(u, v, w);
        }

        printf("Case #%d: ", kase);
        if(!test(maxv+1)) printf("No cycle found.\n");
        else {
            double l = 0, r = maxv;
            while(r - l > 1e-3) {
                //
                double m = l + (r-l)/2;
                if(test(m)) r = m;
                else l = m;
            }
            printf("%.2lf\n", l);
        }
    }
}