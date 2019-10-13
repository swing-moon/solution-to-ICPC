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
#include <unordered_set>

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
int A[maxn], B[maxn], C[maxn];
int F[maxn][maxn];
int n;

void init() {
    Set(A, 0);
    Set(B, 0);
    Set(C, 0);
    Set(F, inf);
}

int main() {
    freopen("input.txt", "r", stdin);
    init();
    scanf("%d", &n);
    _rep(i, 1, n) {
        scanf("%d", &A[i]);
        B[i] = A[i];
    }

    sort(B + 1, B + 1 + n);
    int k = unique(B + 1, B + 1 + n) - B - 1;
    // discrete B[]

    F[0][0] = 0;
    _rep(i, 1, n) {
        int val = F[i - 1][0];
        _rep(j, 1, k) {
            val = min(val, F[i - 1][j]);
            F[i][j] = val + abs(A[i] - B[j]);
        }
    }

    int ans = inf;
    _rep(i, 1, n) {
        ans = min(ans, F[n][i]);
    }
    printf("%d\n", ans);
}