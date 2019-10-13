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

const int maxn = 100001 + 10;

int p[maxn], q[maxn];
int n;

void init() {
    Set(p, 0);
    Set(q, 0);
}

int go(int s) {
    int oil = p[s] - q[s];
    for(int i = (s + 1) % n; i != s; i = (i + 1) % n) {
        if(oil < 0) return i;
        // i is the point cannot reached
        oil += (p[i] - q[i]);
    }
    // s-1 to s, oil < 0, cannot reached s again
    // oil >= 0, means s-1 to s, can go
    if(oil < 0) return -1;
    return s;
}

int solve() {
    int from = 0;
    for( ; ;) {
        int to = go(from);
        if(to < from) return -1;
        if(to == from) return from;
        from = to;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    _rep(kase, 1, T) {
        init();
        scanf("%d", &n);
        _for(i, 0, n) scanf("%d", &p[i]);
        _for(i, 0, n) scanf("%d", &q[i]);

        // input finished, then solve the problem
        int ans = solve();
        printf("Case %d: ", kase);
        if(ans < 0) printf("Not possible\n");
        else printf("Possible from station %d\n", ans + 1);
    }
}