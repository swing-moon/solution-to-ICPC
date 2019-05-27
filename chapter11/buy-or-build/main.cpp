#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int maxn = 1000 + 10;
const int maxq = 8 + 2;

int x[maxn], y[maxn], cost[maxq];
int n;
int pa[maxn];
// n means the number of cities

vector<int> subnet[maxq];
// subnet[i][j] --> {id1, id2, ...}

struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}

    bool operator < (const Edge& rhs) const {
        return w < rhs.w;
    }
};

int dist(int ida, int idb) {
    return (x[ida]-x[idb]) * (x[ida]-x[idb]) + (y[ida]-y[idb]) * (y[ida]-y[idb]);
}

int find(int x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}
// x = id, find(subnet[i][j])

// note: pa[] = find(pa[]), don't write in the function, we need to refresh!
int kruskal(int cnt, vector<Edge>& s, vector<Edge>& fit) {
    if(cnt == 1) return 0;
    // all nodes are connected, we don't need to cost!

    int ans = 0;
    int sz = s.size();

    for(int i = 0; i < sz; i++) {
        // edge s[i]
        int eu = find(s[i].u), ev = find(s[i].v);
        int weight = s[i].w;
        if(eu != ev) {
            pa[eu] = ev;
            cnt--;

            ans += weight;
            fit.push_back(s[i]);

            if(cnt == 1) break;
        }
    }
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    int q;
    // q means the number of subnet;

    while(T--) {
        memset(x, 0, sizeof(x)); memset(y, 0, sizeof(y));
        scanf("%d%d", &n, &q);
        for(int i = 0; i < q; i++) {
            int kase;
            scanf("%d%d", &kase, &cost[i]);
            subnet[i].clear();

            while(kase--) {
                // input id
                int id;
                scanf("%d", &id);
                subnet[i].push_back(id-1);
            }
        }

        // we already got the subnet and q, then we try to get coordinates
        for(int i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]);

        // calculate distance

        // init edge:
        vector<Edge> beg, fit;
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++)
                beg.push_back(Edge(i, j, dist(i, j)));
        }

        sort(beg.begin(), beg.end());
        for(int i = 0; i < n; i++) pa[i] = i;
        // before kruskal, we need to refresh

        int cc = n;
        int ans = kruskal(cc, beg, fit);
        // fit is the appropriate edges in mst

        // enumerate: ans = min(ans, kruskal() )
        for(int mask = 0; mask < (1<<q); mask++) {
            for(int i = 0; i < n; i++) pa[i] = i;

            int c = 0, cc_cnt = n;
            // we made a bug here, we choose bold line from cc(just be calculated!)

            for(int i = 0; i < q; i++) if(mask & (1<<i)) {
                c += cost[i];

                // part kruskal: minus components
                for(int j = 1; j < subnet[i].size(); j++) {
                    int u = find(subnet[i][j]), v = find(subnet[i][0]);
                    if(u != v) {
                        pa[u] = v; cc_cnt--;
                    }
                }
            }

            vector<Edge> subG;
            // update c, cc_cnt;
            ans = min(ans, c + kruskal(cc_cnt, fit, subG));
        }

        printf("%d\n", ans);
        if(T) printf("\n");
    }
    return 0;
}