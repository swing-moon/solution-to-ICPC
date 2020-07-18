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

const int maxn = 70 + 5;
const int inf = 0x3f3f3f3f;
char str[maxn];

const int UP = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int DOWN = 3;

// === init ID ==
map<char, int> ID;
void initID() {
    ID['U'] = 0;
    ID['L'] = 1;
    ID['R'] = 2;
    ID['D'] = 3;
}
// == init finished ==

// == data structure
const char footch[] = ".LR";
int d[maxn][4][4][3];
int act[maxn][4][4][3];

// == compute energy ==
// (f0 != f), return 1
int energy(int a, int ta) {
    if(a == ta) return 3;
    if(a + ta == 3) return 7;
    return 5;
}

int energy(int a, int& ta, int b, int& tb, int f0, int f, int t) {
    ta = a, tb = b;
    if(f == 1) ta = t;
    else if(f == 2) tb = t;

    if(ta == tb) return -1;
    if(ta == RIGHT && tb == LEFT) return -1;
    if(ta == RIGHT && tb != b) return -1;
    if(tb == LEFT && ta != a) return -1;

    int ans = 0;
    if(f == 0) ans = 0;
    else if(f != f0) ans = 1;
    else {
        if(f == 1) ans = energy(a, ta);
        else if(f == 2) ans = energy(b, tb);
    }
    return ans;
}

void update(int i, int a, int b, int f0, int f, int t) {
    int ta, tb;
    int e = energy(a, ta, b, tb, f0, f, t);
    if(e < 0) return;

    int& ans = d[i][a][b][f0];
    int cost = d[i+1][ta][tb][f] + e;

    if(chmin(ans, cost)) {
        act[i][a][b][f0] = f * 4 + t;
    }

}
// == compute finished ==

void initdp() {
    memset(d, 0, sizeof(d));
}

void dp(int n) {
    for(int i = n - 1; i >= 0; i--) {
        _for(a, 0, 4) _for(b, 0, 4) if(a != b) {
            _for(f0, 0, 3) {
                d[i][a][b][f0] = inf;

                if(str[i] == '.') {
                    update(i, a, b, f0, 0, 0);
                    _for(t, 0, 4) {
                        update(i, a, b, f0, 1, t);
                        update(i, a, b, f0, 2, t);
                    }
                }
                else {
                    update(i, a, b, f0, 1, ID[str[i]]);
                    update(i, a, b, f0, 2, ID[str[i]]);
                }
            }
        }
    }
}

void printAns(const int n, int i, int a, int b, int f0) {
    if(i == n) return;

    int f = act[i][a][b][f0] / 4;
    int t = act[i][a][b][f0] % 4;
    printf("%c", footch[f]);

    int na = a, nb = b, nf = f;
    if(f == 1) na = t;
    else if(f == 2) nb = t;

    printAns(n, i + 1, na, nb, nf);
}

void init() {
    memset(d, 0, sizeof(d));
    memset(act, 0, sizeof(act));
}

int main() {
    freopen("input.txt", "r", stdin);

    initID();
    while (scanf("%s", str) == 1) {
        if(str[0] == '#') break;

        init();
        // then dp

        initdp();
        int n = strlen(str);
        dp(n);
        printAns(n, 0, LEFT, RIGHT, 0);
        printf("\n");
    }
}