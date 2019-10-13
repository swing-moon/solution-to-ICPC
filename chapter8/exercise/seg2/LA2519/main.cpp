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

const int maxn = 1000 + 10;

class Seg {
public:
    double l, r;
};

bool cmp(const Seg& lhs, const Seg& rhs) {
    if(lhs.r != rhs.r) return lhs.r < rhs.r;
    else return lhs.l > rhs.l;
}

Seg seg[maxn];
int n, d;

int kase = 1;
bool ok = 1;

void init() {
    ok = 1;
}

int solve() {
    sort(seg, seg + n, cmp);

    int cur = seg[0].r, ans = 1;
    _for(i, 1, n) {
        if(seg[i].l - cur <= 1e-4) continue;

        cur = seg[i].r;
        ans++;
    }

    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &n, &d) == 2 && (n || d)) {
        init();
        _for(i, 0, n) {
            int x, y;
            scanf("%d%d", &x, &y);
            if(ok) {
                if(y > d) {
                    ok = false;
                    continue;
                }
                double dist = sqrt(d * d - y * y);
                seg[i].l = x - dist;
                seg[i].r = x + dist;
            }
        }

        // input finished, then solve the problem
        printf("Case %d: ", kase++);

        if(!ok) printf("-1\n");
        else {
            printf("%d\n", solve());
        }
    }
}