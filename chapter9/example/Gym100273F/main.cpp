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

const double eps = 1e-3;
const int maxn = 10;
const int maxm = 100 + 10;
const int maxstate = 48000;
const int inf = 0x3f3f3f3f;
// 8! states

double c;
int m, n, kk;
int s[maxn], k[maxn];
double price[maxn][maxm];
char name[maxn][10];

// == code states ==
map<vector<int>, int> ID;
vector<vector<int> > states;

// stocks [0...n-1]
void dfs(int d, vector<int>& lots, int tot) {
    if(d == n) {
        ID[lots] = states.size();
        states.push_back(lots);
        return;
    }

    for(int i = 0; i <= k[d] && tot + i <= kk; i++) {
        lots[d] = i;
        dfs(d+1, lots, tot + i);
    }
}

int buy[maxstate][maxn], sell[maxstate][maxn];
void build() {
    vector<int> lots(n);
    dfs(0, lots, 0);

    _for(s, 0, states.size()) {
        int tot = 0;
        for(auto x : states[s]) tot += x;

        _for(i, 0, n) {
            if(tot + 1 <= kk && states[s][i] + 1 <= k[i]) {
                vector<int> nstates(states[s]);
                nstates[i]++;
                buy[s][i] = ID[nstates];
            }

            if(states[s][i] > 0) {
                vector<int> nstates(states[s]);
                nstates[i]--;
                sell[s][i] = ID[nstates];
            }
        }
    }
}
// == code finished ==

// == dp ==
double f[maxm][maxstate];
int pre[maxm][maxstate];
int op[maxm][maxstate];

inline void update(int day, double val, int s, int s2, int id) {
    if(chmax(f[day+1][s2], val)) {
        pre[day+1][s2] = s;
        op[day+1][s2] = id;
    }
}

void initdp() {
    memset(f, -inf, sizeof(f));
    memset(pre, 0, sizeof(pre));
    memset(op, 0, sizeof(op));
}

double dp() {
    f[0][0] = c;
    for(int day = 0; day < m; day++) {
        _for(s, 0, states.size()) {
            if(f[day][s] < -1) continue;

            double val = f[day][s];
            update(day, val, s, s, 0);

            _for(i, 0, n) {
                // deal with ith stock
                if(buy[s][i] >= 0 && val >= price[i][day] - eps) {
                    update(day, val - price[i][day], s, buy[s][i], i + 1);
                }
                if(sell[s][i] >= 0) {
                    update(day, val + price[i][day], s, sell[s][i], - i - 1);
                }
            }
        }
    }
    return f[m][0];
}

void print_ans(int day, int s) {
    if(day == 0) return;
    print_ans(day - 1, pre[day][s]);

    if(op[day][s] == 0) printf("HOLD\n");
    else if(op[day][s] > 0) printf("BUY %s\n", name[op[day][s] - 1]);
    else printf("SELL %s\n", name[-op[day][s] - 1]);
}
// == dp finsihed ==

const string cmd[] = {"HOLD", "BUY", "SELL"};

void init() {
    ID.clear();
    states.clear();
    memset(buy, -1, sizeof(buy));
    memset(sell, -1, sizeof(sell));
}

int main() {
    freopen("fund.in", "r", stdin);

    int kase = 0;
    while (scanf("%lf%d%d%d", &c, &m, &n, &kk) == 4) {
        init();
        if(kase++ > 0) printf("\n");

        // get data
        _for(i, 0, n) {
            scanf("%s%d%d", name[i], &s[i], &k[i]);
            _for(j, 0, m) {
                scanf("%lf", &price[i][j]);
                price[i][j] *= s[i];
            }
        }

        // get data finished
        build();
        initdp();
        double ans = dp();
        printf("%.2lf\n", ans);

        print_ans(m, 0);
    }
}