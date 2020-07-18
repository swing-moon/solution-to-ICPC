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

const int maxn = 300000 + 10;
llong sumc[maxn], sumt[maxn];
llong f[maxn];
int q[maxn], ql, qr;

int n, s;

void init() {
    Set(f, 0x3f);
    f[0] = 0;
    Set(q, 0);
    ql = qr = 0;
}

int bSearch(const int ql, const int qr, int k) {
    int l = ql, r = qr;
    if(l == r) return q[l];

    while (l < r) {
        int mid = (l + r) >> 1;
        if(f[q[mid + 1]] - f[q[mid]] <= k * (sumc[q[mid + 1]] - sumc[q[mid]]) ) l = mid + 1;
        else r = mid;
    }
    return q[l];
}

int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> s;
    init();

    // == get input ==
    _rep(i, 1, n) {
        int t, c;
        scanf("%d%d", &t, &c);
        sumt[i] = sumt[i - 1] + t;
        sumc[i] = sumc[i - 1] + c;
    }
    // == input finished ==

    ql = qr = 1;
    q[1] = 0;

    _rep(i, 1, n) {
        int p = bSearch(ql, qr, sumt[i] + s);
        f[i] = f[p] - (s + sumt[i]) * sumc[p] + sumt[i] * sumc[i] + s * sumc[n];
        while (ql < qr && (f[q[qr]] - f[q[qr - 1]]) * (sumc[i] - sumc[q[qr]]) >= (f[i] - f[q[qr]]) * (sumc[q[qr]] - sumc[q[qr - 1]]) )
            qr--;
        q[++qr] = i;
    }
    cout << f[n] << endl;
}