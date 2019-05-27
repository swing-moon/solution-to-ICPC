#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;
const int maxn = 1000 + 10;
const int maxm = 15000 + 10;
const int inf = 0x3f3f3f3f;
int n, m;

struct Edge {
    int from, to, dist;
};

int cmp(const void* a, const void* b) {
    return (*(Edge*) a).dist - (*(Edge*) b).dist;
    //  a < b sort, from small to large
    // <      we sort by a-b
}

Edge edges[maxm];
int pa[maxn];

int findset(int x) {
    return x == pa[x] ? x : pa[x] = findset(pa[x]);
}

void init() {
    for(int i = 0; i < maxn; i++) pa[i] = i;
}

void kruskal() {
    vector<int> tree;
    int cnt = 0, ans = -inf;
    for(int i = 0; i < m; i++) {
        int u = findset(edges[i].from), v = findset(edges[i].to);
        if(u != v) {
            pa[u] = v;
            ans = max(ans, edges[i].dist);
            tree.push_back(i);
            if(++cnt == n-1) break;
        }
    }

    printf("%d\n", ans);
    printf("%d\n", (int)tree.size());
    for(int i = 0; i < tree.size(); i++) {
        int id = tree[i];
        printf("%d %d\n", edges[id].from, edges[id].to);
    }
}

int main() {
    while(~scanf("%d%d", &n, &m)) {
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &edges[i].from, &edges[i].to, &edges[i].dist);
        }

        // kruskal()
        qsort(edges, m, sizeof(edges[0]), cmp);
        kruskal();
    }
}