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

const int maxn = 100000 + 10;
const double eps = 1e-4;
int L, D, N;

double dcmp(double x) {
    if(fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}

class Seg {
public:
    double l, r;
    Seg(double _l = 0, double _r = 0) : l(_l), r(_r) {}
};

bool cmp(const Seg& lhs, const Seg& rhs) {
    if(dcmp(lhs.r - rhs.r) != 0) return dcmp(lhs.r - rhs.r) < 0;
    else return dcmp(lhs.l - rhs.l) > 0;
}

typedef Seg Point;

Seg seg[maxn];

Seg getSeg(double x, double y) {
    double d = sqrt(D * D - y * y);
    double from = x - d, to = x + d;

    if(dcmp(from) < 0) from = 0;
    if(dcmp(to - L) > 0) to = L;
    return Seg(from, to);
}

int solve() {
    sort(seg, seg + N, cmp);

    int ans = 1;
    double cur = seg[0].r;

    _for(i, 1, N) {
        if(dcmp(seg[i].l - cur) < 0) continue;
        if(dcmp(seg[i].l - cur) > 0) {
            cur = seg[i].r;
            ans++;
        }
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (cin >> L >> D >> N) {
        _for(i, 0, N) {
            double x, y;
            cin >> x >> y;
            seg[i] = getSeg(x, y);
        }
        cout << solve() << endl;
    }
}