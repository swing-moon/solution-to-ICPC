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

const int maxn = 100 + 10;
int n;
int G[maxn][maxn];

void initG() {
    memset(G, 0, sizeof(G));
}

int color[maxn], cc = 0;
vector<int> team[maxn][2];
int diff[maxn];

bool dfs(int u, int c, int cc) {
    color[u] = c;
    team[cc][c-1].push_back(u);

    _for(v, 0, n) {
        if(v == u || (G[u][v] && G[v][u])) continue;
        if(color[v] > 0 && color[v] == color[u]) return false;
        if(!color[v] && !dfs(v, 3-c, cc)) return false;
    }
    return true;
}

bool build() {
    cc = 0;
    _for(u, 0, n) {
        if(!color[u]) {
            team[cc][0].clear();
            team[cc][1].clear();

            if(!dfs(u, 1, cc)) return false;
            diff[cc] = team[cc][0].size() - team[cc][1].size();
            //debug(diff[cc]);
            cc++;
        }
    }
    return true;
}

// == dp ==
int d[maxn][maxn << 1];

void dp() {
    d[0][0+n] = 1;
    _for(i, 0, cc) {
        for(int j = -n; j <= n; j++) if(d[i][j+n]) {
            d[i+1][j+n+diff[i]] = 1;
            d[i+1][j+n-diff[i]] = 1;
        }
    }
}
// == dp finished ==

// == then solve ==
void print_ans(int ans) {
    vector<int> team0, team1;

    int flag = 0;
    for(int i = cc - 1; i >= 0; i--) {
        if(d[i][ans+n-diff[i]]) {
            flag = 0;
            ans -= diff[i];
        }
        else {
            flag = 1;
            ans += diff[i];
        }

        for(auto x : team[i][flag]) team0.push_back(x);
        for(auto x : team[i][flag^1]) team1.push_back(x);
    }

    printf("%d", (int)team0.size());
    for(auto x : team0) printf(" %d", x+1);
    printf("\n");

    printf("%d", (int)team1.size());
    for(auto x : team1) printf(" %d", x+1);
    printf("\n");
}

void solve() {
    _rep(ans, 0, n) {
        if(d[cc][ans+n]) {
            print_ans(ans);
            return;
        }
        if(d[cc][-ans+n]) {
            print_ans(-ans);
            return;
        }
    }
}
// == solve finished ==

void init() {
    memset(color, 0, sizeof(color));
    _for(i, 0, maxn) _for(j, 0, 2) team[i][j].clear();
    memset(diff, 0, sizeof(diff));
    memset(d, 0, sizeof(d));
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    cin >> kase;

    while (kase--) {
        init();
        initG();

        scanf("%d", &n);
        _for(i, 0, n) {
            int v;
            while (scanf("%d", &v) && v) G[i][v-1] = 1;
        }

        // input finished

        if(n == 1 || !build()) {
            printf("No solution\n");
            if(kase) printf("\n");
            continue;
        }

        // then dp
        dp();
        solve();

        if(kase) printf("\n");
    }
}