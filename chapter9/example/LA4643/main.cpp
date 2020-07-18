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

const int maxs = 11;
const int maxn = 128 + 10;
const int inf = 0x3f3f3f3f;
int n, m;
string obj[maxn];
int cnt[(1<<maxs)+1][(1<<maxs)+1];

void _init() {
    memset(cnt, 0, sizeof(cnt));
}


void getdata() {
    _for(i, 0, n) {
        int features = 0;
        _for(k, 0, obj[i].length()) {
            if(obj[i][k] == '1') features |= (1<<k);
        }

        for(int S = 0; S < (1<<m); S++) cnt[S][S & features]++;
    }
}

int d[(1<<maxs)+1][(1<<maxs)+1];
void initdp() {
    memset(d, -1, sizeof(d));
}

int dp(int S, int q) {
    if(cnt[S][q] <= 1) return 0;
    if(cnt[S][q] == 2) return 1;

    int& ans = d[S][q];
    if(ans != -1) return ans;

    ans = m;
    _for(k, 0, m) {
        if(S & (1<<k)) continue;
        int S2 = S | (1<<k), q2 = q | (1<<k);
        if(cnt[S2][q] >= 1 && cnt[S2][q2] >= 1) {
            int val = max(dp(S2, q2), dp(S2, q)) + 1;
            ans = min(ans, val);
        }
    }

    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &m, &n) == 2 && n) {
        _init();
        _for(i, 0, n) cin >> obj[i];

        // get data
        getdata();

        // dp
        initdp();
        int ans = dp(0, 0);
        printf("%d\n", ans);
    }
}