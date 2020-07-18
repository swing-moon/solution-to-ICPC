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

const int maxn = 100 + 10;
int f[maxn][maxn];
const int inf = 0x3f3f3f3f;

int A[maxn][maxn], N, M;
int pre[maxn][maxn];

void initdp() {
    Set(f, -inf);
    Set(pre, 0);
    _for(i, 0, maxn) f[0][i] = 0;
}

int dp() {
    _rep(i, 1, N) _rep(j, i, M - (N - i)) {
            int& ans = f[i][j];
            _for(k, i - 1, j) {
                int tmp = f[i - 1][k] + A[i][j];
                if(tmp > ans) {
                    ans = tmp;
                    pre[i][j] = k;
                }
            }
        }

    int ans = -inf;
    _rep(i, 1, M) ans = max(ans, f[N][i]);
    return ans;
}


void print(int i, int j) {
    if(i == 0) return;
    print(i - 1, pre[i][j]);
    printf("%d ", j);
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &N, &M);

    _rep(i, 1, N) _rep(j, 1, M) scanf("%d", &A[i][j]);

    // then dp()
    initdp();
    int res = dp();
    printf("%d\n", res);
    int j;
    _rep(i, 1, M) if(f[N][i] == res) j = i;

    print(N, j);
}