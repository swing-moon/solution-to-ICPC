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

const int maxn = 5000 + 5;
const int inf = 0x3f3f3f3f;

int N;
int F[maxn][maxn], P[maxn][maxn];
int a[maxn];
int sum[maxn];

void init() {
    Set(F, inf);
    Set(P, 0);
    Set(sum, 0);

    _rep(i, 1, N) {
        F[i][i] = 0;
        P[i][i] = i;
    }
}

void dp() {
    init();
    _rep(i, 1, N) {
        scanf("%d", &a[i]);
        sum[i] = sum[i - 1] + a[i];
    }

    _forDown(i, N - 1, 1) _rep(j, i + 1, N) {
        _rep(k, P[i][j - 1], P[i + 1][j]) {
            int val = F[i][k] + F[k + 1][j] + (sum[j] - sum[i - 1]);
            if(val < F[i][j]) {
                F[i][j] = val;
                P[i][j] = k;
            }
        }
    }

    printf("%d\n", F[1][N]);
}

int main() {
    freopen("input.txt", "r", stdin);
    while (cin >> N && N) {
        dp();
    }
}