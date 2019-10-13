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
const double eps = 1e-7;

int dcmp(double x) {
    if(fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}

class Seg {
public:
    int from, to;
    bool operator< (const Seg& rhs) const {
        return from <= rhs.from;
    }
};

Seg seg[maxn];
int n;

bool solve(const double len) {
    double lastr = 0;
    _for(i, 0, n) {
        Seg& cur = seg[i];
        lastr = max((double)cur.from, lastr) + len;

        if(lastr > cur.to) return false;
    }
    return true;
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void output(double x) {
    double _p = floor(x + eps);
    if(dcmp(_p - x) == 0) {
        printf("%.0lf/1\n", _p);
        return;;
    }

    int p = 1, q = 1;
    double ans = 1;

    _rep(i, 1, n) {
        int pp = (int)(floor(x * (double)i + 0.5));
        double tmp = (double)pp / i;

        if(fabs(tmp - x) < fabs(ans - x)) {
            p = pp;
            q = i;
            ans = tmp;
        }
    }

    int g = gcd(p, q);
    printf("%d/%d\n", p / g, q / g);
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &n) == 1) {
        _for(i, 0, n) {
            scanf("%d%d", &seg[i].from, &seg[i].to);
        }
        sort(seg, seg + n);

        double l = 1, r = (double)1000000.0 / n;
        double mid;
        assert(dcmp(l - r) <= 0);

        _for(t, 0, 50) {
            mid = (l + r) / 2;
            if(!solve(mid)) r = mid;
            else l = mid;
        }

        // output (l + r) / 2
        //debug((l + r) / 2 );
        output((l + r) / 2);
    }
}