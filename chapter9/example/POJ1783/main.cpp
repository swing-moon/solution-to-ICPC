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
typedef long long ll;
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
#define MPR(a, b) make_pair(a, b)

const int maxn = 50000 + 5;
int N, tot;
ll ans, a[maxn];

void init() {
    tot = 1;
    ans = 0;
}

void dfs(int k) {
    ll tmp = a[k] + a[k - 1];
    ans += tmp;
    tot--;

    // for successor, move right
    _for(i, k, tot) a[i] = a[i + 1];

    // for pre, while a[i - 1] < tmp, move left
    int i = 0;
    for(i = k - 1; i >= 1 && a[i - 1] < tmp; i--) a[i] = a[i - 1];

    a[i] = tmp;

    while (i >= 2 && a[i] >= a[i - 2]) {
        int r = tot - i;
        dfs(i - 1);
        i = tot - r;
    }

}

void GarsiaWachs() {
    _for(i, 0, N) scanf("%lld", &a[i]);
    _for(i, 1, N) {
        a[tot++] = a[i];
        while (tot >= 3 && a[tot - 1] >= a[tot - 3]) dfs(tot - 2);
    }
    while (tot > 1) dfs(tot - 1);
    printf("%lld\n", ans);
}

int main() {
    freopen("input.txt", "r", stdin);
    while (cin >> N && N) {
        init();
        GarsiaWachs();
    }
}