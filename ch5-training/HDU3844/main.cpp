#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <algorithm>

using namespace std;
typedef long long llong;

struct ID {
    map<int, int> m;
    int cnt;
    ID() : cnt(0) {}

    int get(int x) {
        if(!m.count(x)) m[x] = cnt++;
        return m[x];
    }
};

struct Edge {
    int from, to;
};

const int maxn = 100000 + 10;
int pre[maxn], iscut[maxn], idx[maxn], dfs_clock, bcc_cnt;
vector<int> G[maxn], bcc[maxn];

stack<Edge> stk;

int tarjan(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;
    int cld = 0;

    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        Edge e = (Edge) {u, v};

        if(!pre[v]) {
            cld++; stk.push(e);

            int lowv = tarjan(v, u);
            lowu = min(lowu, lowv);
            if(lowv >= pre[u]) {
                iscut[u] = true;
                bcc_cnt++; bcc[bcc_cnt].clear();

                for(;;) {
                    Edge x = stk.top(); stk.pop();
                    if(idx[x.from] != bcc_cnt) {
                        idx[x.from] = bcc_cnt;
                        bcc[bcc_cnt].push_back(x.from);
                    }
                    if(idx[x.to] != bcc_cnt) {
                        idx[x.to] = bcc_cnt;
                        bcc[bcc_cnt].push_back(x.to);
                    }
                    if(x.from == u && x.to == v) break;
                }
            }
        }
        else if(pre[v] < pre[u] && v != fa) {
            stk.push(e);
            lowu = min(lowu, pre[v]);
        }
    }
    if(fa < 0 && cld == 1) iscut[u] = 0;
    return lowu;
}

int main() {
    int kase = 0, n;
    while(scanf("%d", &n) == 1 && n) {
        memset(pre, 0, sizeof(pre));
        memset(iscut, 0, sizeof(iscut));
        memset(idx, 0, sizeof(idx));
        for(int i = 0; i < maxn; i++) G[i].clear();
        dfs_clock = bcc_cnt = 0;

        ID id;
        for(int i = 0; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            u = id.get(u); v = id.get(v);
            G[u].push_back(v); G[v].push_back(u);
        }

        tarjan(0, -1);

        llong ans1 = 0, ans2 = 1;
        for(int i = 1; i <= bcc_cnt; i++) {
            int cut_cnt = 0;
            for(int j = 0; j < bcc[i].size(); j++) {
                if(iscut[bcc[i][j]]) cut_cnt++;
            }

            if(cut_cnt == 1) {
                ans1++; ans2 *= (llong)(bcc[i].size() - cut_cnt);
            }
        }

        if(bcc_cnt == 1) {
            ans1 = 2; ans2 = bcc[1].size() * (bcc[1].size()-1) / 2;
        }

        printf("Case %d: %lld %lld\n", ++kase, ans1, ans2);
    }
}