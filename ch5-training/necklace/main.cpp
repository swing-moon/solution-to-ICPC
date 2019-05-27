#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxc = 50;

int n, G[maxc+1][maxc+1], deg[maxc+1];

struct Edge {
    int from, to;
    Edge(int from, int to) : from(from), to(to) {}
};

vector<Edge> ans;

void euler(int u) {
    for(int v = 1; v <= maxc; v++) {
        if(G[u][v]) {
            G[u][v]--; G[v][u]--;
            euler(v);
            ans.push_back(Edge(u, v));
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);

    for(int kase = 1; kase <= T; kase++) {
        scanf("%d", &n);
        memset(G, 0, sizeof(G));
        memset(deg, 0, sizeof(deg));

        int s = -1;
        for(int i = 0; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u][v]++; G[v][u]++;
            deg[u]++; deg[v]++;
            s = u;
        }

        bool ok = true;
        for(int i = 1; i <= maxc; i++) {
            if(deg[i] % 2 == 1) { ok = false; break; }
        }

        if(ok) {
            // find euler path
            ans.clear();
            euler(s);
            if(ans.size() != n || ans[0].to != ans[ans.size()-1].from) ok = false;
        }

        printf("Case #%d\n", kase);
        if(!ok)
            printf("some beads may be lost\n");
        else
            for(int i = ans.size()-1; i >= 0; i--) {
                printf("%d %d\n", ans[i].from, ans[i].to);
            }

        if(kase < T) printf("\n");
    }
}