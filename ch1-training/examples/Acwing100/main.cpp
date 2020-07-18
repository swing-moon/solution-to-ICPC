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
#define Cpy(a, b) memcpy(a, b, sizeof(b))
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

const int maxn = 1e5 + 10;
int A[maxn], B[maxn];
int n;

void init() {
    Set(B, 0);
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    init();

    _rep(i, 1, n) scanf("%d", &A[i]);

    B[1] = 1;
    _rep(i, 2, n) B[i] = A[i] - A[i - 1];

    ll s1 = 0, s2 = 0;
    _rep(i, 2, n) {
        if(B[i] > 0) s1 += B[i];
        else s2 -= B[i];
    }

    ll ans = min(s1, s2) + abs(s1 - s2);
    cout << ans << endl;

    ll ans2 = abs(s1 - s2) + 1;
    cout << ans2 << endl;
}