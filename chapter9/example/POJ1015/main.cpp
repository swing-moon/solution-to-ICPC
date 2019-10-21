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

const int base = 400, maxn = 200 + 10, maxk = 800 + 5;
const int maxm = 20 + 5;
const int inf = 0x3f3f3f3f;


vector<int> ans;
int f[maxm][maxk];
int p[maxn], d[maxn];
int sump, sumd;

struct St {
    int i, j, k;
};

St st[maxn][maxm][maxk];

void init() {
    ans.clear();
    Set(f, -inf);
    Set(p, 0);
    Set(d, 0);

    f[0][0 + base] = 0;
    sump = sumd = 0;
}

int N, M;


int dp() {
    _rep(i, 1, N) {
        _rep(j, 0, M) _rep(k, 0, base * 2) st[i][j][k] = {i - 1, j, k};

        for(int j = M; j; j--) {
            _rep(k, 0, base * 2) {
                if((k - (p[i] - d[i])) < 0 || (k - (p[i] - d[i])) > 800) continue;
                if(f[j - 1][k - (p[i] - d[i])] + p[i] + d[i] > f[j][k]) {
                    f[j][k] = f[j - 1][k - (p[i] - d[i])] + p[i] + d[i];
                    st[i][j][k] = {i - 1, j - 1, k - (p[i] - d[i])};
                }
            }
        }
    }

    int ret = 0;
    _rep(k, 0, 400) {
        if(f[M][400 + k] >= 0 && f[M][400 + k] >= f[M][400 - k]) {
            ret = 400 + k;
            break;
        }

        if(f[M][400 - k] >= 0) {
            ret = 400 - k;
            break;
        }
    }
    return ret;
}

void print(int i, int j, int k) {
    if(j == 0) return;
    const St pre = st[i][j][k];
    print(pre.i, pre.j, pre.k);

    if(pre.j != j && f[pre.j][pre.k] >= 0) {
        ans.push_back(i);
        sump += p[i];
        sumd += d[i];
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int kase = 1;
    while ((cin >> N >> M) && (M || N)) {
        //debug(M);
        init();
        printf("Jury #%d\n", kase++);

        _rep(i, 1, N) {
            cin >> p[i] >> d[i];
        }

        // then dp;
        int ansk = dp();
        print(N, M, ansk);


        printf("Best jury has value %d for prosecution and value %d for defence:\n", sump, sumd);
        //printf("(%d %d)", sump, sumd);
        // puts("");
        _for(i, 0, ans.size()) printf(" %d", ans[i]);
        printf("\n\n");
    }
}