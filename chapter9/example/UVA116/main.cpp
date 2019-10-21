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

const int maxm = 10 + 5, maxn = 100 + 5;
const int inf = 0x3f3f3f3f;

int A[maxm][maxn];
int M, N;

int f[maxm][maxn];
int nxt[maxm][maxn];

int first = 0;
int ans = inf;

void initDP() {
    first = 0;
    ans = inf;

    Set(f, inf);
    Set(nxt, 0);
    //_rep(i, 1, M) f[i][N] = A[i][N];

    // dp _forDown(j = N - 1 down to 1)
}
int dp() {
    _forDown(j, N, 1) _rep(i, 1, M) {
            if(j == N) {
                f[i][j] = A[i][j];
                //debug(f[i][j]);
            }
            else {
                //
                int ni[3] = {i - 1, i, i + 1};
                int nj = j + 1;

                if(i == 1) ni[0] = M;
                if(i == M) ni[2] = 1;

                sort(ni, ni + 3);

                _for(k, 0, 3) {
                    if(f[i][j] > f[ni[k]][nj] + A[i][j]) {
                        assert(ni[k] != 0 && ni[k] != M + 1);
                        f[i][j] = f[ni[k]][nj] + A[i][j];
                        nxt[i][j] = ni[k];
                    }
                }

            }
            if(j == 1 && ans > f[i][j]) {
                assert(f[i][j] != inf);
                ans = f[i][j];
                first = i;
            }

        }
    return ans;
}

void print(int i, int j) {
    if(j > N) return;

    if(j != 1) printf(" ");
    printf("%d", i);
    print(nxt[i][j], j + 1);
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &M, &N) == 2 && M) {
        //debug(N);
        _rep(i, 1, M) _rep(j, 1, N) {
            scanf("%d", &A[i][j]);
            //debug(A[i][j]);
        }

        // dp
        initDP();
        int ret = dp();

        //print(first, 1);
        printf("%d", first);
        for(int u = nxt[first][1], j = 2; j <= N; j++, u = nxt[u][j - 1]) printf(" %d", u);

        printf("\n%d\n", ret);
    }
}