#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
const int maxn = 1000 + 10;

struct Edge {
    int from, to, weight;
};

bool cmp(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

Edge edges[maxn];
int cnt = 0;
void addEdge(int from, int to, int weight) {
    edges[cnt++] = (Edge){from, to, weight};
}

int read() {
    int x; scanf("%d", &x); return x;
}

int pa[maxn];
int find(int x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}


int n, m;

vector<Edge> ans;

void kruskal() {
    for(int i = 0; i < n; i++) pa[i] = i;
    m = cnt;
    sort(edges, edges+m, cmp);

    for(int i = 0; i < m; i++) {
        Edge& e = edges[i];
        int u = find(e.from), v = find(e.to);

        if(u != v) {
            pa[u] = v;
            ans.push_back(e);
        }
    }
}


int main() {

    n = read(), m = read();
    for(int i = 0; i < m; i++) {
        int u, v, w;
        u = read(); v = read(); w = read(); u--; v--;
        addEdge(u, v, w);
        // addEdge(v, u, w);
    }

    kruskal();
    printf("%d\n", ans[ans.size()-1].weight);
    printf("%d\n", ans.size());
    for(int i = 0; i < ans.size(); i++) {
        printf("%d %d \n", ans[i].from+1, ans[i].to+1);
    }


}