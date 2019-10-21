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

const int maxn = 30 + 5;
const int maxm = 5000 + 5;
const int inf = 0x3f3f3f3f;
int N, M;
int g[maxn], f[maxn][maxm];
int S[maxn];
int prei[maxn][maxm], prej[maxn][maxm];
int ans[maxn];

struct Cld {
    int g;
    int id;

    bool operator< (const Cld& rhs) const {
        return g > rhs.g;
    }
};
Cld cld[maxn];

void initDP() {
    Set(f, inf);
    Set(S, 0);

    f[0][0] = 0;

    _rep(i, 1, N) S[i] = S[i - 1] + cld[i].g;
}

int dp() {
    initDP();

    _rep(i, 1, N) _rep(j, i, M) {
        f[i][j] = f[i][j - i];
        //debug(f[i][j]);
        prei[i][j] = i;
        prej[i][j] = j - i;

        _for(k, 0, i) {
            int sum = k * (S[i] - S[k]);
            if(sum + f[k][j - (i - k)] < f[i][j]) {
                f[i][j] = sum + f[k][j - (i - k)];
                prei[i][j] = k;
                prej[i][j] = j - (i - k);
            }
        }
    }
    return f[N][M];
}

void printAns(int i, int j) {
    if(i == 0) return;

    //debug(prei[i][j]), debug(prej[i][j]);
    printAns(prei[i][j], prej[i][j]);
    //debug(prei[i][j]), debug(prej[i][j]);

    if(i == prei[i][j]) {
        _rep(u, 1, i) ans[cld[u].id]++;
    }
    else {
        _rep(u, prei[i][j] + 1, i) ans[cld[u].id] = 1;
    }
    return;
}

int main() {
    freopen("cookies.in","r",stdin);
    freopen("cookies.out", "w", stdout);
    scanf("%d%d", &N, &M);

    _rep(i, 1, N) {
        int _g;
        scanf("%d", &_g);

        cld[i].g = _g;
        cld[i].id = i;
    }

    sort(cld + 1, cld + 1 + N);
    // then dp
    cout << dp() << endl;
    printAns(N, M);

    _rep(i, 1, N) {
        if(i != 1) printf(" ");
        printf("%d", ans[i]);
    }
    cout << endl;
}