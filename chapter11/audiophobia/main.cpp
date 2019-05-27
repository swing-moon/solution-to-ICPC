#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int maxn = 100 + 10;
const int maxm = 1000 + 10;
const int inf = 1000000000;

int n, m, q;
int d[maxn][maxn];

int main() {
    int kase = 0;

    while(scanf("%d%d%d", &n, &m, &q) == 3 && n) {
        // m edges
        int u, v, w;
//        memset(d, -inf, sizeof(d));
//        for(int i = 0; i < n; i++) d[i][i] = 0;
        for(int i = 0; i < n; i++) {
            d[i][i] = 0;
            for(int j = i+1; j < n; j++)
                d[i][j] = d[j][i] = inf;
        }

        while(m--) {
            scanf("%d%d%d", &u, &v, &w);
            // get data
            d[u-1][v-1] = min(d[u-1][v-1], w);
//            d[u-1][v-1] = w;
            d[v-1][u-1] = d[u-1][v-1];
        }

        // floyd()
        for(int k = 0; k < n; k++)
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++) if(d[i][k] < inf && d[k][j] < inf)
                    d[i][j] = min(d[i][j], max(d[i][k], d[k][j]));

        int q1, q2;
        if(kase > 0) printf("\n");
        printf("Case #%d\n", ++kase);

        while(q--) {
            scanf("%d%d", &q1, &q2);
//            cout << d[q1-1][q2-1] << endl;
            if(d[q1-1][q2-1] == inf) printf("no path\n");
            else printf("%d\n", d[q1-1][q2-1]);
        }
    }
}