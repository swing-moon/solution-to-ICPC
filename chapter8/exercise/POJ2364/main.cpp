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

const int maxn = 1000 + 5;
int lh, rh, lhi, rhi;
int l, r;
int lx[maxn], rx[maxn];

int leftx, rightx;

void init() {
    Set(lx, 0);
    Set(rx, 0);
    lh = rh = 0;
}

int solve() {
    if(lh == rh) {
        int lt = 0, rt = 0;
        for(int i = l, h = lx[l]; i > lhi; i--) {
            lt += h;
            h = max(h, lx[i - 1]);
        }

        for(int i = r, h = rx[r]; i > rhi; i--) {
            rt += h;
            h = max(h, rx[i - 1]);
        }

        return (lhi + rhi + 1) * lh * 2 + min(lt, rt) * 2 * 2;
    }

    int M = min(lh, rh), lgi = 0, rgi = 0;
    // water can reach at most x = lgi or rgi
    // the first higher than M
    // [lgi, rgi] is the rectangle area

    while (lgi < l && lx[lgi] < M) lgi++;
    while (rgi < r && rx[rgi] < M) rgi++;
    // [lhi, rgi] is the rectangle area
    // [lgi, rhi] is the rectangle area

    int lt = 0, rt = 0;
    int t = 0;
    if(lh < rh) {
        for(int i = l, h = lx[l]; i > lhi; i--)  {
            lt += h;
            h = max(h, lx[i - 1]);
        }
        // right we may not reach rhi, just fill at rgi

        for(int i = rgi, h = M; rx[i] <= M; i++) {
            rt += h;
            h = max(h, rx[i + 1]);
        }

        t = lt > rt ? (lt + rt) : 2 * lt;
    }

    if(lh > rh) {
        for(int i = r, h = rx[r]; i > rhi; i--) {
            rt += h;
            h = max(h, rx[i - 1]);
        }

        for(int i = lgi, h = M; lx[i] <= M; i++) {
            lt += h;
            h = max(h, lx[i + 1]);
        }

        t = rt > lt ? (lt + rt) : 2 * rt;
    }

    return t * 2 + (lgi + rgi + 1) * 2 * M;
}

int main() {
    freopen("input.txt", "r", stdin);

    while (cin >> leftx >> rightx && leftx && rightx) {
        init();

        l = (-leftx) / 2, r = rightx / 2;

        for(int i = leftx; i < 0; i += 2) {
            int ii = (-i) / 2;
            cin >> lx[ii];

            if(lx[ii] >= lh) lh = lx[ii], lhi = ii;
        }

        for(int i = 1; i <= rightx; i += 2) {
            int ii = i / 2;
            cin >> rx[ii];

            if(rx[ii] > rh) rh = rx[ii], rhi = ii;
        }

        // then solve the problem
        printf("%d\n", solve());
    }
}