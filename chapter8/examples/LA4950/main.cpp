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
char grid[maxn][maxn];
int height[maxn], ans[maxn * 2];

int n, m;

class Rec {
public:
    int c, h;
    Rec(int _c = 0, int _h = 0) : c(_c), h(_h) {}
};

Rec stk[maxn];

void init() {
    Set(height, 0);
    Set(ans, 0);
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);

    while (kase--) {
        init();
        scanf("%d%d", &n, &m);
        _for(i, 0, n) scanf("%s", grid[i]);

        _for(i, 0, n) {
            int top = -1;
            _for(j, 0, m) {
                if(grid[i][j] == '#') {
                    top = -1;
                    height[j] = 0;
                }
                else {
                    // land can be sold
                    height[j]++;
                    Rec cur(j, height[j]);

                    if(top < 0) stk[++top] = cur;
                    else {
                        while(top >= 0 && stk[top].h >= cur.h) cur.c = stk[top--].c;
                        if(top < 0 || stk[top].h - stk[top].c < cur.h - cur.c) stk[++top] = cur;
                    }

                    ans[j - stk[top].c + stk[top].h + 1]++;
                }
            }
        }
        _rep(i, 1, n + m) if(ans[i]) printf("%d x %d\n", ans[i], i * 2);
    }
}