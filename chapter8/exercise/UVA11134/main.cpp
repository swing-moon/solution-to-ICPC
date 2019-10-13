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

const int maxn = 5000 + 5;
int n;

class Seg {
public:
    int l, r;
    Seg(int _l = 0, int _r = 0) : l(_l), r(_r) {}
};

Seg segx[maxn], segy[maxn];
int ansx[maxn], ansy[maxn];

bool solve(Seg* seg, int* ans) {
    fill(ans, ans + n, -1);

    _rep(x, 1, n) {
        int chose = -1, minr = n + 1;

        _for(i, 0, n) {
            if(x >= seg[i].l) {
                if(ans[i] < 0 && seg[i].r < minr) {
                    minr = seg[i].r;
                    chose = i;
                }
            }
        }

        if(minr < x || chose < 0) return false;

        ans[chose] = x;
    }
    return true;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &n) == 1 && n) {
        _for(i, 0, n) cin >> segx[i].l >> segy[i].l >> segx[i].r >> segy[i].r;

        if(solve(segx, ansx) && solve(segy, ansy)) {
            _for(i, 0, n) printf("%d %d\n", ansx[i], ansy[i]);
        }
        else printf("IMPOSSIBLE\n");
    }
}