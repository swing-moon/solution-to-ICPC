#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int maxn = 100 + 10;
const int inf = 0x3f3f3f3f;
int m, n;

int pa[maxn];
int find(int x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}

struct Edge {
    int uid, vid, w;
    Edge(int uid , int vid, int w) : uid(uid), vid(vid), w(w) {}

    bool operator < (const Edge& rhs) const {
        return w < rhs.w;
    }
};

vector<Edge> e;

int kruskal() {
    int m = e.size();
    sort(e.begin(), e.end());

    // for l = 0 to m --> e[l].uid

    int ans = inf;
    for(int l = 0; l < m; l++) {
        for(int i = 1; i <= n; i++) pa[i] = i;

        int tot = n;
        for(int r = l; r < m; r++) {
            int u = find(e[r].uid), v = find(e[r].vid);
            if(u != v) {
                pa[u] = v;
                if(--tot == 1) {
                    ans = min(ans, e[r].w - e[l].w);
                    break;
                }
            }
        }
    }

    if(ans == inf) ans = -1;
    return ans;
}

int main() {
    int uid, vid, w;
    while(scanf("%d%d", &n, &m) == 2 && n) {
        //
        e.clear();
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &uid, &vid, &w);
            e.push_back(Edge(uid, vid, w));
        }
        int res = kruskal();
        printf("%d\n", res);
    }
}