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

const int maxn = 1000 + 5;
double f[maxn][maxn], D[maxn][maxn];
int N, M;
int x, y;

void init() {
    Set(f, 0);
    Set(D, 0);
}

void dp() {
    _forDown(i, N - 1, x) {
        D[1][1] = D[M][M] = 2.0 / 3.0;
        D[1][M + 1] = f[i + 1][1] / 3.0 + 1;

        D[1][2] = D[M][M - 1] = -1 / 3.0;
        D[M][M + 1] = f[i + 1][M] / 3.0 + 1;

        _rep(j, 2, M - 1) {
            D[j][j - 1] = D[j][j + 1] = -1 / 4.0;
            D[j][j] = 3.0 / 4.0;
            D[j][M + 1] = f[i + 1][j] / 4.0 + 1;
        }
        // row of matrix finished
        _rep(j, 1, M) {
            double r = D[j + 1][j] / D[j][j];

            D[j + 1][j] = 0;
            D[j + 1][j + 1] -= r * D[j][j + 1];
            D[j + 1][M + 1] -= r * D[j][M + 1];
        }
        _forDown(j, M, 1) {
            double r = D[j - 1][j] / D[j][j];

            D[j - 1][j] = 0;
            D[j - 1][M + 1] -= r * D[j][M + 1];

            f[i][j] = D[j][M + 1] / D[j][j];
        }
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    scanf("%d%d", &N, &M);
    scanf("%d%d", &x, &y);
    init();

    if(M == 1) {
        printf("%d\n", (N - x) * 2);
        return 0;
    }
    dp();
    printf("%.4lf\n", f[x][y]);
}