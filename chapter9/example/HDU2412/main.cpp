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

const int maxn = 200 + 10;
map<string, int> mp;
int tot = 0;
int n;
vector<int> son[maxn];

int ID(const string& str) {
    if(!mp.count(str)) mp[str] = tot++;
    return mp[str];
}

int d[maxn][2];
int f[maxn][2];

void initdp() {
    Set(d, 0);
    Set(f, 0);
}

int dp(int u, int k) {
    d[u][k] = k;
    f[u][k] = 1;
    for(auto v : son[u]) {
        if(k == 1) {
            d[u][k] += dp(v, 0);
            f[u][k] &= f[v][0];
        }
        else {
            d[u][k] += max(dp(v, 0), dp(v, 1));
            if(d[v][0] == d[v][1]) f[u][k] = 0;
            else if(d[v][0] > d[v][1] && f[v][0] == 0) f[u][k] = 0;
            else if(d[v][1] > d[v][0] && f[v][1] == 0) f[u][k] = 0;
        }
    }

    return d[u][k];
}

void init() {
    mp.clear();
    tot = 0;

    _for(i, 0, maxn) son[i].clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    string s, s2;
    while (cin >> n >> s) {
        init();

        ID(s);
        _for(i, 1, n) {
            cin >> s2 >> s;
            son[ID(s)].push_back(ID(s2));
        }

        // then dp
        initdp();
        int ans = max(dp(0, 1), dp(0, 0));
        printf("%d ", ans);

        bool flag = true;
        if(d[0][0] == d[0][1]) flag = false;
        else if(d[0][1] > d[0][0] && f[0][1] == 0) flag = false;
        else if(d[0][0] > d[0][1] && f[0][0] == 0) flag = false;

        flag == 0 ? printf("No\n") : printf("Yes\n");
    }
}