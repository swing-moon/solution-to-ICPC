#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

const int maxn = 8, maxnode = 1 << maxn;
int n, lcnt;
int leaves[maxnode+1], idx[maxn];
char buf[maxnode+1];

int solve(const char* vva) {
    int l = 0, r = lcnt - 1;
    // travel leaves[]

    for(int i = 0; i < n; i++) {
        int k = idx[i], mid = (l+r) >> 1;
        if(vva[k] == '1') l = mid+1;
        else r = mid;
    }

    return leaves[l];
}


int main() {
    int kase = 1, m, x;
    while(scanf("%d", &n) == 1 && n) {
        //
        lcnt = 1 << n;
        for(int i = 0; i < n; i++) {
            //
            scanf("%s", buf);
            sscanf(buf+1, "%d", &x);
            idx[i] = x-1;
        }

        scanf("%s", buf);
        for(int i = 0; i < lcnt; i++) leaves[i] = buf[i] - '0';

        scanf("%d", &m);
        printf("S-Tree #%d:\n", kase++);

        for(int i = 0; i < m; i++) {
            scanf("%s", buf);
            printf("%d", solve(buf));
        }
        puts("\n");
    }
}