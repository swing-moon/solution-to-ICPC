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

const int maxs = 8;
const int maxn = 100 + 20 + 5;
const int inf = 0x3f3f3f3f;

int m, n, s;
int st[maxn], c[maxn];

int d[maxn][(1<<maxs)+1][(1<<maxs)+1];

void initdp() {
    memset(d, -1, sizeof(d));
}

int dp(int i, int s0, int s1, int s2) {
    if(i == m + n) return s2 == (1<<s)-1 ? 0 : inf;
    int& ans = d[i][s1][s2];

    if(ans >= 0) return ans >= inf ? inf : ans;

    ans = inf;
    if(i >= m) ans = dp(i+1, s0, s1, s2);

    int v1 = s0 & st[i], v2 = s1 & st[i];
    s0 ^= v1;
    s1 = (s1 ^ v2) | v1;
    s2 |= v2;

    ans = min(ans, dp(i+1, s0, s1, s2) + c[i]);

    return ans;
}


int main() {
    freopen("input.txt", "r", stdin);
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        ss >> s >> m >> n;
        if(s == 0) break;

        _for(i, 0, n + m) {
            getline(cin, line);
            stringstream ss(line);

            ss >> c[i];
            int x;
            st[i] = 0;
            while (ss >> x) {
                x--;
                st[i] |= (1<<x);
            }
        }

        // input finished
        // dp

        initdp();
        int ans = dp(0, (1<<s)-1, 0, 0);
        printf("%d\n", ans);
    }
}