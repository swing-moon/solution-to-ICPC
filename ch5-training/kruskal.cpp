#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 100 + 10;
const int inf = 0x3f3f3f3f;
int m, n;
int pa[maxn];

int find(x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
    // init REP(i, n) pa[i] = i;
}

struct Edge {
    //
    int from, to, weight;
    bool operator < (const Edge& rhs) const {
        //
        return weight < rhs.weight;
    }
};

vector<Edge> edges;

int kruskal() {
    m = edges.size();
    for(int i = 0; i < n; i++) pa[i] = i;

    sort(edges.begin(), edges.end());
    int ans = 0;
    for(int i = 0; i < m; i++) {
        Edge& e = edges[i];
        int u = find(e.from), v = find(e.to);

        if(u != v) {
            ans += e.weight; pa[u] = v;
        }
    }
    return ans;
}