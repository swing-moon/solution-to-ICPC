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

const int maxn = 2000 + 10;
const int inf = 0x3f3f3f3f;

int A[maxn], F[maxn][maxn];
int A2[maxn];
int n;

void init() {
    Set(A, 0);
    Set(A2, 0);
    ///Set(B, 0);
    Set(F, inf);
}

int query(int x, int m) {
    return lower_bound(A2 + 1, A2 + 1 + m, x) - A2;
}

int main() {
    freopen("input.txt", "r", stdin);
    init();
    scanf("%d", &n);

    _rep(i, 1, n) {
        scanf("%d", &A[i]);
        A2[i] = A[i];
    }

    sort(A2 + 1, A2 + 1 + n);
    int m = unique(A2 + 1, A2 + 1 + n) - A2 - 1;
    // id = query(A[i], m)

    F[0][0] = 0;

    _rep(i, 1, n) {
        int val = F[i - 1][0];

        _rep(j, 1, m) {
            int baseline = A2[j];
            val = min(val, F[i - 1][j]);

            F[i][j] = val + abs(A[i] - baseline);
        }
    }

    int ans = inf;
    _rep(j, 1, m) ans = min(ans, F[n][j]);
    cout << ans << endl;

}