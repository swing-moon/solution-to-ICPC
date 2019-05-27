#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 9;
int v[maxn], n;

bool is_sorted() {
    for(int i = 0; i < n-1; i++)
        if(v[i] >= v[i+1])  return false;

    return true;
}

// how many integers with incorrect successor?

int h() {
    int cnt = 0;
    for(int i = 0; i < n-1; i++) {
        if(v[i] + 1 != v[i+1])  cnt++;
    }

    if(v[n-1] != n) cnt++;
    return cnt;
}

bool dfs(int d, int maxd) {
    if( (h()-0) > 3 * (maxd-d) )  return false;
    if(is_sorted())  return true;

    int b[maxn], oldv[maxn];
    memcpy(oldv, v, sizeof(v));

    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            // cut apart!
            int cnt = 0;
            for(int k = 0; k < n; k++) {
                if(k < i || k > j) b[cnt++] = v[k];
            }

            // joint!
            for(int k = 0; k <= cnt; k++) {
                int cnt2 = 0;
                for(int m = 0; m < k; m++)  v[cnt2++] = b[m];
                for(int m = i; m <= j; m++) v[cnt2++] = oldv[m];
                for(int m = k; m < cnt; m++) v[cnt2++] = b[m];

                if(dfs(d+1, maxd))  return true;
                memcpy(v, oldv, sizeof(oldv));
            }
        }
    }
    return false;
}

int solve() {
    if(is_sorted()) return 0;
    int max_ans = 10;
    for(int maxd = 1; maxd < max_ans; maxd++) {
        if(dfs(0, maxd)) return maxd;
    }
    return max_ans;
}


int main() {
    int kase = 0;
    while(scanf("%d", &n) == 1 && n) {
        for(int i = 0; i < n; i++)  scanf("%d", &v[i]);
        printf("Case %d: %d\n", ++kase, solve());
    }
    return 0;
}