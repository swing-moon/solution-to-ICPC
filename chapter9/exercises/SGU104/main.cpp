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

void initdp() {
    Set(f, -inf);
    _for(i, 0, maxn) f[0][i] = 0;
}

int dp() {
    _rep(i, 1, N) _rep(j, i, M - (N - i)) {
        _for(k, i - 1, j) {
            f[i][j] = max(f[i][j], f[i - 1][k] + A[i][j]);
        }
    }

    int ans = -inf;
    _rep(i, 1, M) ans = max(ans, f[N][i]);
    return ans;
}

void print(int ans)  {
    vector<int> pos;
    _forDown(i, N, 1) {
        int p = M;
        _forDown(j, M, 1) if(f[i][j] == ans) p = j;
        pos.push_back(p);
        ans -= A[i][p];
    }
    reverse(pos.begin(), pos.end());
    _for(i, 0, pos.size()) printf("%d ", pos[i]);
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &N, &M);

    _rep(i, 1, N) _rep(j, 1, M) scanf("%d", &A[i][j]);

    // then dp()
    initdp();
    int res = dp();
    printf("%d\n", res);
    print(res);
}