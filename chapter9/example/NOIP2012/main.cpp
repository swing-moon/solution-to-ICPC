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
#define lowbit(i) (i & (-i))
#define MPR(a, b) make_pair(a, b)

const int maxn = 100000 + 5, inf = 0x3f3f3f3f;
const int maxlog = 20;
int N, lgN, m;
int h[maxn], x[maxn], s[maxn];
int ga[maxn], gb[maxn];
int f[maxlog][maxn][2], da[maxlog][maxn][2], db[maxlog][maxn][2];
int la = 0, lb = 0;

multiset<pair<int, int> > st;
typedef multiset<pair<int, int> >::iterator SII;
SII it1, it2, it3, it4, it;

void init() {
    st.clear();
    st.insert(make_pair(inf, 0));
    st.insert(make_pair(-inf, 0));
    st.insert(make_pair(inf, 0));
    st.insert(make_pair(-inf, 0));
    h[0] = 0;
    Set(ga, 0);
    Set(gb, 0);
    la = lb = 0;
}

// pair(value, id)
inline void calg() {
    for(int i = N; i; i--) {
        st.insert(MPR(h[i], i));
        it = st.find(MPR(h[i], i));

        it1 = (++it);
        it2 = (++it);
        it3 = (--(--(--it)));
        it4 = (--it);

        int a = (*it3).first != -inf ? h[i] - (*it3).first : inf;
        int b = (*it1).first != inf ? (*it1).first - h[i] : inf;
        if(a <= b) {
            // choose it3 as gb[]
            gb[i] = (*it3).second;
            // (it1, it4) cmp
            a = (*it4).first != -inf ? h[i] - (*it4).first : inf;
            ga[i] = (a <= b ? (*it4).second : (*it1).second);
        } else {
            // choose it1 as gb[]
            gb[i] = (*it1).second;
            b = (*it2).first != inf ? (*it2).first - h[i] : inf;
            ga[i] = (a <= b ? (*it3).second : (*it2).second);
        }
    }
}

void calf() {
    _rep(i, 1, N) {
        f[0][i][0] = ga[i];
        f[0][i][1] = gb[i];
    }
    _rep(i, 1, N) {
        f[1][i][0] = f[0][ f[0][i][0] ][1];
        f[1][i][1] = f[0][ f[0][i][1] ][0];
    }
    _for(i, 2, lgN) {
        _rep(j, 1, N) {
            f[i][j][0] = f[i-1][ f[i-1][j][0] ][0];
            f[i][j][1] = f[i-1][ f[i-1][j][1] ][1];
        }
    }
}

void cald() {
    _rep(i, 1, N) {
        da[0][i][0] = abs(h[i] - h[ga[i]]);
        db[0][i][1] = abs(h[i] - h[gb[i]]);
        da[0][i][1] = db[0][i][0] = 0;
    }
    _rep(i, 1, N) {
        da[1][i][0] = da[0][i][0];
        db[1][i][1] = db[0][i][1];

        da[1][i][1] = da[0][ f[0][i][1] ][0];
        db[1][i][0] = db[0][ f[0][i][0] ][1];
    }

    _for(i, 2, lgN) _rep(j, 1, N) _for(k, 0, 2) {
        da[i][j][k] = da[i-1][j][k] + da[i-1][ f[i-1][j][k] ][k];
        db[i][j][k] = db[i-1][j][k] + db[i-1][ f[i-1][j][k] ][k];
    }
}

void calS(int S, int X) {
    // always start from A, A first
    la = lb = 0;
    int p = S;
    _forDown(i, lgN, 0) {
        if(f[i][p][0] && la + lb + da[i][p][0] + db[i][p][0] <= X) {
            la += da[i][p][0];
            lb += db[i][p][0];
            p = f[i][p][0];
        }
    }
}

void solve1() {
    calS(1, x[0]);
    // ans1 (pID, heightValue)
    //double ans1[2] = {1, (lb ? (double)la / lb : inf)};
    pair<int, double> ans1 = MPR(1, (double)(lb ? (double)la / lb : inf));
    _rep(i, 2, N) {
        calS(i, x[0]);
        if((double)la / lb < ans1.second || ((double)la / lb == ans1.second && h[i] > h[ans1.first])) {
            ans1 = MPR(i, (double)la / lb);
        }
    }
    cout << ans1.first << endl;
}

void solve2() {
    _rep(i, 1, m) {
        calS(s[i], x[i]);
        //cout << s[i] << " " << x[i] << endl;
        printf("%d %d\n", la, lb);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    cin >> N;
    lgN = log(N) / log(2.0);
    // debug(lgN);
    _rep(i, 1, N) scanf("%d", &h[i]);
    cin >> x[0] >> m;
    _rep(i, 1, m) scanf("%d%d", &s[i], &x[i]);

    // input finished, then solve
    init();
    calg();
    calf();
    cald();
    solve1();
    solve2();
}