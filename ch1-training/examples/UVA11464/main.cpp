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

pair<int, int> crack(int n) {
    int st = sqrt(n);
    int fac = n / st;
    while (n % st) {
        st += 1;
        fac = n / st;
    }

    return make_pair(st, fac);
}

inline ll qpow(ll a, int n) {
    ll ans = 1;
    for(; n; n >>= 1) {
        if(n & 1) ans *= 1ll * a;
        a *= a;
    }
    return ans;
}

template <class T>
inline bool chmax(T& a, T b) {
    if(a < b) {
        a = b;
        return true;
    }
    return false;
}

template <class T>
inline bool chmin(T& a, T b) {
    if(a > b) {
        a = b;
        return true;
    }
    return false;
}

// ============================================================== //

const int maxn = 15 + 5;
const int inf = 0x3f3f3f3f;
int a[maxn][maxn], b[maxn][maxn];
int n;

bool valid(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

int check(const int val) {
    memset(b, 0, sizeof(b));
    _for(k, 0, n) {
        if(val & (1<<k)) b[1][n - k] = 1;
    }

    _rep(i, 2, n) _rep(j, 1, n) {
        int sum = 0;
        if(valid(i - 1, j - 1)) sum += b[i - 1][j - 1];
        if(valid(i - 2, j)) sum += b[i - 2][j];
        if(valid(i - 1, j + 1)) sum += b[i - 1][j + 1];

        b[i][j] = sum % 2;
    }

    int cnt = 0;
    _rep(i, 1, n) _rep(j, 1, n) {
        if(a[i][j] == 1 && b[i][j] == 0) return inf;
        if(a[i][j] == 0 && b[i][j] == 1) cnt++;
    }
    return cnt;
}

void init() {
    memset(b, 0, sizeof(b));
}


int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    cin >> kase;

    int t = 0;
    while (kase--) {
        printf("Case %d: ", ++t);
        init();
        scanf("%d", &n);
        _rep(i, 1, n) _rep(j, 1, n) {
            scanf("%d", &a[i][j]);
        }

        // then solve
        int ans = inf;
        _for(k, 0, (1<<n)) ans = min(ans, check(k));
        if(ans == inf) printf("-1\n");
        else printf("%d\n", ans);
    }
}