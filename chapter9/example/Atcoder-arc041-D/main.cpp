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
#define Cpy(a, b) memcpy(a, b, sizeof(b))
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

const int maxn = 5000 + 10;
int n, m;
int f[maxn], C[maxn];

void initDP() {
    Set(f, 0);
    f[0] = 1;

    int mid = n >> 1;
    _rep(i, 2, mid + 1) C[i] = i - 1;
    _rep(i, mid + 2, n) C[i] = n - i + 2;
}

int dp() {
    initDP();

    _rep(i, 2, n) _rep(j, C[i], n - 1) {
        f[j] = (f[j] + f[j - C[i]]) % m;
    }

    ll ans = 0;
    _rep(i, 0, n - 1) {
        ans = ans + 1ll * (n - i) * f[i] % m;
        ans %= m;
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);

    int res = dp();
    cout << res << endl;
}