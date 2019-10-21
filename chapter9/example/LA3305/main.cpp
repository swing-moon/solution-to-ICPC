#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <bitset>
#include <assert.h>

using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _forS(i, l, r) for(set<int>::iterator i = (l); i != (r); i++)
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define _forDown(i, l, r) for(int i = (l); i >= r; i--)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;
#define debugArr(arr, x, y) _for(i, 0, x) { _for(j, 0, y) printf("%c", arr[i][j]); printf("\n"); }
#define _forPlus(i, l, d, r) for(int i = (l); i + d < (r); i++)
#define lowbit(i) (i & (-i))

const int maxn = 1000 + 5;
const int inf = 0x3f3f3f3f;

class Node {
public:
    double x, y;
};

Node nodes[maxn];
int N;
double f[maxn][maxn];

double dist(int i, int j) {
    return sqrt((nodes[i].x - nodes[j].x) * (nodes[i].x - nodes[j].x) + (nodes[i].y - nodes[j].y) * (nodes[i].y - nodes[j].y));
}

void initdp() {
    Set(f, 0.0);
}

double dp(int i, int j) {
    double& ans = f[i][j];
    if(ans > 0) return ans;

    if(i == N - 1) {
        //
        ans = dist(N - 1, N) + dist(j, N);
    }
    else {
        //
        ans = min(dp(i + 1, j) + dist(i, i + 1), dp(i + 1, i) + dist(i + 1, j));
    }

    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &N) == 1) {
        _rep(i, 1, N) scanf("%lf%lf", &nodes[i].x, &nodes[i].y);

        // then dp()
        initdp();
        double ret = dp(2, 1);

        printf("%.2lf\n", ret + dist(2, 1));
    }

}