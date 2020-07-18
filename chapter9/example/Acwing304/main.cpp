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
typedef long double ld;
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

const int maxn = 100000 + 5;
int N, L, P;

class Q {
public:
    int x, l, r;
};
Q q[maxn];

ld f[maxn];
ll S[maxn];

void init() {
    Set(f, 0);
    Set(S, 0);
}

ld cal(int i, int j) {
    ld ans = 1;
    ld num = abs((ld)(S[i] - S[j] + i - j - 1 - L));
    _rep(k, 1, P) ans *= num;
    return ans + f[j];
}

int bsearch(int i, int ql, int qr) {
    int ans = 0;
    while (ql <= qr) {
        int mid = (ql + qr) >> 1;
        if(q[mid].l <= i && q[mid].r >= i) {
            ans = mid;
            break;
        }
        if(q[mid].l <= i) ql = mid + 1;
        else qr = mid - 1;
    }

    return q[ans].x;
}

int findpos(int i, int x, int l, int r) {
    while (l < r) {
        int mid = (l + r) >> 1;
        if (cal(mid, i) > cal(mid, x)) l = mid + 1;
        else r = mid;
    }
    return l;
}

void insert(int i, int& ql, int& qr) {
    int pos = -1;
    while (ql <= qr) {
        int lt = q[qr].l, rt = q[qr].r, xt = q[qr].x;
        if(cal(lt, i) <= cal(lt, xt)) pos = q[qr--].l;
        else {
            if(cal(rt, i) < cal(rt, xt)) {
                pos = findpos(i, xt, q[qr].l, q[qr].r);
                q[qr].r = pos - 1;
            }
            break;
        }
    }

    if(pos != -1) {
        q[++qr].l = pos;
        q[qr].r = N;
        q[qr].x = i;
    }
}

void solve() {
    init();
    cin >> N >> L >> P;

    // == get poetry sentences ==
    _rep(i, 1, N) {
        char str[35];
        scanf("%s", str);
        S[i] = S[i - 1] + strlen(str);
    }
    // == poetry sentences finished ==

    // == monotonic dp ==
    int ql = 1, qr = 1;
    q[1].x = 0;
    q[1].l = 1;
    q[1].r = N;

    _rep(i, 1, N) {
        int j = bsearch(i, ql, qr);
        if(i == 1) assert(j == 0);
        f[i] = cal(i, j);

        // == then pop front and try to insert i ==
        while (ql <= qr && q[ql].r <= i) ql++;
        q[ql].l = i + 1;
        insert(i, ql, qr);
        // == monotonic queue finished ==
    }
    // == monotonic finished ==

    if(f[N] > 1e18) puts("Too hard to arrange");
    else cout << (ll)f[N] << endl;

    _rep(i, 1, 20) putchar('-');
    cout << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    cin >> T;
    while (T--) solve();
}