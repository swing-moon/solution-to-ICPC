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

const int maxn = 1000 + 5;
const int inf = 0x3f3f3f3f;
const double eps = 1e-4;

double d[maxn][maxn][2];
double sum[maxn];
int n;
double x0, v;

struct A {
    double x;
    double c;
    double d;

    A() {}
    A(double x, double c, double d) : x(x), c(c), d(d) {}

    bool operator< (const A& rhs) const {
        return x < rhs.x;
    }
} a[maxn];

void initdp() {
    memset(d, -1, sizeof(d));
}

double cost(double x1, double x2, int l, int r) {
    return fabs(x1-x2) / v * (sum[l-1] + sum[n] - sum[r]);
}

double dp(int l, int r, int flag) {
    double& ans = d[l][r][flag];
    if(ans >= 0) return ans;

    if(l == r) {
        if(fabs(a[l].x - x0) <= eps) {
            ans = 0;
            return ans;
        }
        else {
            ans = inf;
            return ans;
        }
    }

    ans = inf;
    if(flag == 0) {
        ans = min(ans, dp(l+1, r, 0)+ cost(a[l+1].x, a[l].x, l+1, r) + a[l].c);
        ans = min(ans, dp(l+1, r, 1) + cost(a[r].x, a[l].x, l+1, r) + a[l].c);
    }
    if(flag) {
        ans = min(ans, dp(l, r-1, 1) + cost(a[r-1].x, a[r].x, l, r-1) + a[r].c);
        ans = min(ans, dp(l, r-1, 0) + cost(a[l].x, a[r].x, l, r-1) + a[r].c);
    }

    return ans;
}

void init() {
    memset(sum, 0, sizeof(sum));
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%lf%lf", &n, &v, &x0) == 3 && n) {
        init();

        _rep(i, 1, n) {
            scanf("%lf%lf%lf", &a[i].x, &a[i].c, &a[i].d);
        }
        a[++n] = A(x0, 0, 0);
        sort(a + 1, a + 1 + n);

        _rep(i, 1, n) sum[i] = sum[i - 1] + a[i].d;
        //debug(sum[n]);

        // then dp
        initdp();
        double ans = min(dp(1, n, 0), dp(1, n, 1));
        //debug(ans);
        printf("%.0lf\n", floor(ans));
    }
}