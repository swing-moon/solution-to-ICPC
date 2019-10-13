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

const int maxn = 1000000 + 10;
int A[maxn];

map<int, int> last;
int pre[maxn];
int n;

void init() {
    Set(A, 0);
    Set(pre, 0);
    last.clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    while(scanf("%d", &T) != EOF) {
        while (T--) {
            init();
            scanf("%d", &n);

            _for(i, 0, n) {
                scanf("%d", &A[i]);
                if (!last.count(A[i])) pre[i] = -1;
                else pre[i] = last[A[i]];
                last[A[i]] = i;
            }

            int R = 0, ans = 0;
            _for(L, 0, n) {
                while (R < n && pre[R] < L) R++;
                ans = max(ans, R - L);
            }
            printf("%d\n", ans);
        }
    }
}