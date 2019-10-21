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

const int maxn = 50 + 10;
int A[maxn][maxn];
int M, N;
int F[maxn * 2][maxn][maxn];

void init() {
    //
    Set(A, 0);
}

void initDP() {
    //
    Set(F, -1);
    F[0][1][1] = A[1][1];
}

void dp() {
    //
    _for(i, 0, M + N - 2) {
        for(int x1 = 1; x1 <= M && x1 <= i + 1; x1++) {
            int y1 = i + 2 - x1;
            for(int x2 = 1; x2 <= M && x2 <= i + 1; x2++) {
                int y2 = i + 2 - x2;

                // both right, both down
                if(x1 == x2) {
                    F[i + 1][x1][x2] = max(F[i + 1][x1][x2], F[i][x1][x2] + A[x1][y1 + 1]);
                    F[i + 1][x1 + 1][x2 + 1] = max(F[i + 1][x1 + 1][x2 + 1], F[i][x1][x2] + A[x1 + 1][y1]);
                }
                else {
                    F[i + 1][x1][x2] = max(F[i + 1][x1][x2], F[i][x1][x2] + A[x1][y1 + 1] + A[x2][y2 + 1]);
                    F[i + 1][x1 + 1][x2 + 1] = max(F[i + 1][x1 + 1][x2 + 1], F[i][x1][x2] + A[x1 + 1][y1] + A[x2 + 1][y2]);
                }


                // x1 down, x2 right
                if(x2 == x1 + 1) {
                    F[i + 1][x1 + 1][x2] = max(F[i + 1][x1 + 1][x2], F[i][x1][x2] + A[x1 + 1][y1]);
                }
                else F[i + 1][x1 + 1][x2] = max(F[i + 1][x1 + 1][x2], F[i][x1][x2] + A[x1 + 1][y1] + A[x2][y2 + 1]);

                // x1 right, x2 down
                if(x1 == x2 + 1) {
                    F[i + 1][x1][x2 + 1] = max(F[i + 1][x1][x2 + 1], F[i][x1][x2] + A[x1][y1 + 1]);
                }
                else F[i + 1][x1][x2 + 1] = max(F[i + 1][x1][x2 + 1], F[i][x1][x2] + A[x1][y1 + 1] + A[x2 + 1][y2]);
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    init();
    scanf("%d%d", &M, &N);

    _rep(i, 1, M) _rep(j, 1, N) scanf("%d", &A[i][j]);

    // then initDP() and dp()
    initDP();
    dp();

    cout << F[N + M - 2][M][M] << endl;
}