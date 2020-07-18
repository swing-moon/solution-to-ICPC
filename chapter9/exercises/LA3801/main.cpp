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
int n, m;
int a[maxn][maxn], d[maxn][maxn];

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

struct Pos {
    int x, y;
    Pos() {}
    Pos(int x, int y) : x(x), y(y) {}
};

bool valid(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= m;
}

bool cango(const Pos& pos) {
    bool flag = false;
    for(int dir = 0; dir < 4; dir++) {
        int nx = pos.x + dx[dir];
        int ny = pos.y + dy[dir];
        if(!valid(nx, ny)) continue;

        if(a[nx][ny] < a[pos.x][pos.y]) {
            flag = true;
            break;
        }
    }
    return flag;
}

void initdp() {
    memset(d, -1, sizeof(d));

    _rep(i, 1, n) _rep(j, 1, m) {
        if(!cango(Pos(i, j))) {
            d[i][j] = 1;
        }
    }
}

int dp(int i, int j) {
    if(d[i][j] >= 0) return d[i][j];

    int& ans = d[i][j];

    for(int dir = 0; dir < 4; dir++) {
        int nx = i + dx[dir];
        int ny = j + dy[dir];

        if(!valid(nx, ny)) continue;
        if(a[nx][ny] >= a[i][j]) continue;

        ans = max(ans, dp(nx, ny) + 1);
    }

    return ans;
}

void init() {
    memset(d, -1, sizeof(d));
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    cin >> kase;
    while (kase--) {
        init();
        string name;
        cin >> name;
        printf("%s: ", name.c_str());

        scanf("%d%d", &n, &m);
        _rep(i, 1, n) _rep(j, 1, m) scanf("%d", &a[i][j]);

        // then solve
        initdp();
        //_rep(i, 1, n) _rep(j, 1, m) if(d[i][j] == 1) debug(a[i][j]);

        int ans = -1;
        _rep(i, 1, n) _rep(j, 1, m) ans = max(ans, dp(i, j));

        printf("%d\n", ans);
    }
}