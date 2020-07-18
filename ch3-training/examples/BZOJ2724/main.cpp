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

const int maxn = 40000 + 5;
const int T = 800 + 5;
int f[T][T];
int n, m, t;
int a[maxn], b[maxn];
int ct[maxn];
vector<int> show[maxn];

map<int, int> loc;

class Seg {
public:
    int l, r;
};

Seg seg[maxn];
int pos[maxn];

void init() {
    Set(pos, 0);
    Set(f, 0);
    _for(i, 0, maxn) show[i].clear();
    Set(ct, 0);

    loc.clear();
}

void discrete() {
    sort(b + 1, b + 1 + n);
    int tot = unique(b + 1, b + 1 + n) - b - 1;

    _rep(i, 1, n) {
        a[i] = lower_bound(b + 1, b + 1 + tot, a[i]) - b;
        show[a[i]].push_back(i);
    }

}



void split(const int len) {
    _rep(i, 1, t) {
        seg[i].l = (i - 1) * len + 1;
        seg[i].r = i * len;
    }
    if(seg[t].r < n) {
        t++;
        seg[t].l = seg[t - 1].r + 1;
        seg[t].r = n;
    }

    _rep(i, 1, n) {
        _rep(j, seg[i].l, seg[i].r) pos[j] = i;
    }
}

inline void cal() {
    _rep(i, 1, t) {
        int ans = 0, cnt = 0;
        Set(ct, 0);

        _rep(j, seg[i].l, n) {
            ct[a[j]]++;
            if(cnt < ct[a[j]] || (cnt == ct[a[j]] && a[j] < ans)) {
                cnt = ct[a[j]];
                ans = a[j];
            }

            f[i][pos[j]] = ans;
        }
    }
}

int count(int x, int l, int r) {
    return upper_bound(show[x].begin(), show[x].end(), r) - lower_bound(show[x].begin(), show[x].end(), l);
}

void update(int x, int l, int r, int &ans, int &cnt) {
    int c = count(x, l, r);
    if(c > cnt || (c == cnt && x < ans)) {
        cnt = c;
        ans = x;
    }
}

int ask(int l, int r) {
    int p = pos[l], q = pos[r];
    int ans = 0, cnt = 0;
    if(p == q) {
        _rep(i, l, r) update(a[i], l, r, ans, cnt);
        return b[ans];
    }

    int x = 0, y = 0;
    if(p + 1 <= q - 1) {
        x = p + 1;
        y = q - 1;
    }

    _rep(i, l, seg[p].r) update(a[i], l, r, ans, cnt);
    _rep(i, seg[q].l, r) update(a[i], l, r, ans, cnt);
    if(f[x][y]) update(f[x][y], l, r, ans, cnt);

    //debug(ans);
    return b[ans];
}

int main() {
    freopen("input.txt", "r", stdin);
    init();
    cin >> n >> m;
    _rep(i, 1, n) scanf("%d", &a[i]);
    Cpy(b, a);


    // == discrete ==
    discrete();
    // == discrete finished ==



    // == part ==
    t = sqrt(n * log(n) / log(2));
    int len = t ? n / t : n;

    // == split ==
    split(len);
    // == split finished ==

    // == calculate f() ==
    cal();
    // == f() finished==

    // == main algorithm ==
    int res = 0;
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);

        l = (l + res - 1) % n + 1;
        r = (r + res - 1) % n + 1;
        //debug(l), debug(r);

        if(l > r) swap(l, r);
        res = ask(l, r);
        printf("%d\n", res);
    }

}