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
int h[maxn];
int n, w[maxn];
int stk[maxn];

llong ans;

void init() {
    Set(h, 0);
    Set(w, 0);
    Set(stk, 0);
    ans = 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    while(cin >> n && n) {
        init();
        _rep(i, 1, n) scanf("%d", &h[i]);

        int p = 0;
        _rep(i, 1, n + 1) {
            if(h[i] > stk[p]) {
                stk[++p] = h[i];
                w[p] = 1;
            }
            else {
                int width = 0;
                while(stk[p] > h[i]) {
                    width += w[p];
                    ans = max(ans, (long long)width * stk[p]);
                    p--;
                }
                stk[++p] = h[i];
                w[p] = width + 1;
            }
        }
        cout << ans << endl;
    }
}