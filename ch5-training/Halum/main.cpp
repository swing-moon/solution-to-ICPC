#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 500 + 10;
const int maxm = 2700 + 10;

struct Edge {
    int to, weight;
};

struct Bellman {
    int n, m;
    Edge edges[maxm];

    int head[maxn], next[maxm];
    // indicate id of edge

    bool inq[maxn];
    int cnt[maxn], d[maxn];

    void init(int n) {
        this->n = n;
        m = 0;
        memset(head, -1, sizeof(head));
    }

    void addEdge(int from, int to, int weight) {
        next[m] = head[from];
        head[from] = m;
        edges[m++] = (Edge){to, weight};
    }

    bool negaCycle() {
        queue<int> q;
        memset(inq, 0, sizeof(inq));
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < n; i++) {
            d[i] = 0; q.push(i);
        }

        while(!q.empty()) {
            int x = q.front(); q.pop(); inq[x] = false;
            for(int i = head[x]; i != -1; i = next[i]) {
                Edge& e = edges[i];
                if(d[e.to] > d[x] + e.weight) {
                    d[e.to] = d[x] + e.weight;
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

bool test(int flow) {
    //
    for(int i = 0; i < bell.m; i++) {
        bell.edges[i].weight -= flow;
    }

    bool ret = bell.negaCycle();

    for(int i = 0; i < bell.m; i++) bell.edges[i].weight += flow;
    return !ret;
}

int main() {
    int n, m;
    while(scanf("%d%d", &n, &m) == 2) {
        bell.init(n);
        int ub = 0;
        for(int i = 0; i < m; i++) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d); u--; v--;
            ub = max(ub, d);
            bell.addEdge(u, v, d);
        }

        if(test(ub+1)) printf("Infinite\n");
        else if(!test(1)) printf("No Solution\n");
        else {
            //
            int L = 2, R = ub, ans = 1;
            while(L < R) {
                int M = L + (R-L+1)/2;
                if(test(M)) {
                    ans = M;
                    L = M;
                } else {
                    R = M-1;
                }
            }

            printf("%d\n", ans);
        }
    }
}