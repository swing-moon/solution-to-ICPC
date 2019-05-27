#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;
const int maxn = 100 + 10;
const int inf = 0x3f3f3f3f;

struct Edge {
    int from, to, weight;
    bool operator < (const Edge& rhs) const {
        return weight < rhs.weight;
    }
};

int pa[maxn];

int find(int x) {
    // remember init pa[i] = i;
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}

vector<Edge> edges;


int N, Q, m;

int read() {
    int k; scanf("%d", &k); return k;
}

int kruskal() {
    m = edges.size();
    sort(edges.begin(), edges.end());
    /*
    for(int i = 0; i < edges.size(); i++) printf("%d ", edges[i].weight);
    printf("\n");
    */

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

int main() {
    scanf("%d", &N);

    int x;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            x = read(); if(i == j) continue;
            edges.push_back((Edge){i, j, x});
        }
    }

    // add Q;
    for(int i = 0; i < N; i++) pa[i] = i;
    Q = read();

    for(int kase = 0; kase < Q; kase++) {
        int u = read(), v = read(); u--, v--;
        int pu = find(u), pv = find(v);
        if(pu != pv) pa[pu] = pv;
    }

    // kruskal()
    printf("%d\n", kruskal());

}