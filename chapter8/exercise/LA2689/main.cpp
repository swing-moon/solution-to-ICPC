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

const int maxn = 100 + 4;

class Point {
public:
    int x, y;
    bool operator< (const Point& rhs) const {
        if(x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
};

Point P[maxn];
int dy[maxn];
int ans, ansX, ansY;

void init() {
    Set(dy, 0);
    ans = ansX = ansY = 0;
}

int N, W, H;

void solve() {
    int n = unique(dy, dy + N + 2) - dy;
    _for(i, 0, n) _for(j, i + 1, n) {
        int minY = dy[i], maxY = dy[j];
        int hh = maxY - minY, last = 0, ww = 0;

        _for(k, 0, N) {
            Point& cur = P[k];
            if(cur.y <= minY || cur.y >= maxY) continue;

            ww = cur.x - last;
            if(ans < min(ww, hh)) {
                ans = min(ww, hh);
                ansX = last, ansY = minY;
            }
            last = cur.x;
        }

        ww = W - last;
        if(ans < min(ww, hh)) {
            ans = min(ww, hh);
            ansX = last, ansY = minY;
        }
    }
    printf("%d %d %d\n", ansX, ansY, ans);
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    while (T--) {
        init();
        scanf("%d%d%d", &N, &W, &H);

        _for(i, 0, N) {
            scanf("%d%d", &P[i].x, &P[i].y);
            dy[i] = P[i].y;
        }
        dy[N] = 0, dy[N + 1] = H;

        // discrete
        sort(dy, dy + N + 2);
        sort(P, P + N);

        solve();
        if(T) printf("\n");
    }
}