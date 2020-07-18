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
typedef long long ll;
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

const int maxn = 20000 + 10;
int n, m;
int A[maxn], B[maxn];


void solve() {
    sort(A, A + n);
    sort(B, B + m);

    int cur = 0;
    int ans = 0;
    _for(i, 0, m) {
        if(B[i] >= A[cur]) {
            ans += B[i];
            cur++;

            if(cur == n) break;
        }
    }

    if(cur < n) printf("Loowater is doomed!\n");
    else printf("%d\n", ans);
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) == 2 && n) {
        _for(i, 0, n) scanf("%d", &A[i]);
        _for(i, 0, m) scanf("%d", &B[i]);

        solve();
    }
}