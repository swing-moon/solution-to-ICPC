#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

using namespace std;
const int maxn = 100000 + 10;

struct TwoSAT {
    int n;
    vector<int> G[maxn*2];
    bool mark[maxn*2];
    stack<int> stk;

    bool dfs(int u) {
        if(mark[u^1]) return false;
        if(mark[u]) return true;

        mark[u] = true;
        stk.push(u);
        for(int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            if(!dfs(v)) return false;
        }
        return true;
    }

    void init(int n) {
        this->n = n;
        memset(mark, 0, sizeof(mark));
        for(int i = 0; i < n*2; i++) G[i].clear();
    }

    void addEdge(int x, int xflag, int y, int yflag) {
        x = x*2 + xflag;
        y = y*2 + yflag;
        G[x^1].push_back(y);
        G[y^1].push_back(x);
    }

    bool solve() {
        for(int i = 0; i < n*2; i += 2) {
            if(!mark[i] && !mark[i+1]) {
                if(!dfs(i)) {
                    while(!stk.empty()) {
                        int x = stk.top(); stk.pop();
                        mark[x] = 0;
                    }
                    if(!dfs(i+1)) return false;
                }
            }
        }
        return true;
    }
};

int n, m, total_age, age[maxn];
TwoSAT twosat;

int is_young(int k) {
    return age[k]*n < total_age;
}


int main() {
    while(scanf("%d%d", &n, &m) == 2 && n) {
        total_age = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &age[i]);
            total_age += age[i];
        }

        twosat.init(n);
        for(int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v); u--; v--;

            if(u == v) continue;
            twosat.addEdge(u, 1, v, 1);
            if(is_young(u) == is_young(v)) {
                twosat.addEdge(u, 0, v, 0);
            }
        }

        if(!twosat.solve()) printf("No solution.\n");
        else for(int i = 0; i < n; i++) {
            if(twosat.mark[i*2]) printf("C\n");
            else if(is_young(i)) printf("B\n");
            else printf("A\n");
        }
    }
}