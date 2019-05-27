#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <cmath>

using namespace std;
const int maxn = 2000 + 10;

struct TwoSAT {
    int n;
    vector<int> G[maxn*2];
    bool mark[maxn*2];
    stack<int> stk;

    void init(int n) {
        this->n = n;
        memset(mark, 0, sizeof(mark));
        for(int i = 0; i < n*2; i++) G[i].clear();
    }

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

    void addEdge(int x, int xflag, int y, int yflag) {
        x = x*2 + xflag;
        y = y*2 + yflag;
        G[x^1].push_back(y);
        G[y^1].push_back(x);
    }

    bool solve() {
        //
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

TwoSAT twosat;
int n, T[maxn][2];

bool OK(int dist) {
    //
    twosat.init(n);
    for(int i = 0; i < n; i++) for(int ki = 0; ki < 2; ki++) {
        for(int j = i+1; j < n; j++) for(int kj = 0; kj < 2; kj++) {
            if(abs(T[i][ki] - T[j][kj]) < dist) twosat.addEdge(i, ki^1, j, kj^1);
        }
    }
    return twosat.solve();
}

int main() {
    while(scanf("%d", &n) == 1 && n) {
        int L = 0, R = 0;
        for(int i = 0; i < n; i++) for(int ki = 0; ki < 2; ki++) {
            scanf("%d", &T[i][ki]);
            R = max(R, T[i][ki]);
        }
        // binary-search
        // check OK()

        while(L < R) {
            int M = L + (R-L+1)/2;
            if(OK(M)) L = M;
            else R = M-1;
        }

        printf("%d\n", L);
    }
}