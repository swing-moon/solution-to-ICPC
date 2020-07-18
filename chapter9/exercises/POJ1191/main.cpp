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

const int N = 8;
const int maxn = 15 + 2;

int f[maxn][N + 2][N + 2][N + 2][N + 2];
int A[N + 2][N + 2];
int n;
int S[N + 2][N + 2];
double tot = 0;
const int inf = 0x3f3f3f3f;

void init() {
    Set(f, inf);
    Set(S, 0);

    _rep(i, 1, N) _rep(j, 1, N) {
            S[i][j] = S[i-1][j] + S[i][j-1] - S[i-1][j-1] + A[i][j];
        }

    _rep(x1, 1, N) _rep(y1, 1, N) {
            _rep(x2, x1, N) _rep(y2, y1, N) {
                    int t = S[x2][y2] - S[x2][y1-1] - S[x1-1][y2] + S[x1-1][y1-1];
                    f[0][x1][y1][x2][y2] = t * t;
                }
        }
}

void dp(int k, int x1, int y1, int x2, int y2) {
    int& ans = f[k][x1][y1][x2][y2];
    ans = inf;

    _for(a, x1, x2) {
        ans = min(ans, f[k-1][x1][y1][a][y2] + f[0][a+1][y1][x2][y2]);
        ans = min(ans, f[k-1][a+1][y1][x2][y2] + f[0][x1][y1][a][y2]);
    }

    _for(b, y1, y2) {
        ans = min(ans, f[k-1][x1][y1][x2][b] + f[0][x1][b+1][x2][y2]);
        ans = min(ans, f[k-1][x1][b+1][x2][y2] + f[0][x1][y1][x2][b]);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);

    _rep(i, 1, N) _rep(j, 1, N) {
            scanf("%d", &A[i][j]);
            tot += A[i][j];
        }

    init();
    _rep(k, 1, n - 1) _rep(x1, 1, N) _rep(y1, 1, N) {
                _rep(x2, x1, N) _rep(y2, y1, N) {
                        dp(k, x1, y1, x2, y2);
                    }
            }

    double avr = (double)(tot / n);
    //debug(tot);
    double ans = sqrt(1.0 * f[n - 1][1][1][N][N] / n - (avr * avr));
    printf("%.3f\n", ans);
}