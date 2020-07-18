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

const int maxn = 300 + 5;
int score[maxn];
vector<int> son[maxn];
int N, M;

int f[maxn][maxn];
const int inf = 0xcf;

void initdp() {
    Set(f, inf);
}

void dp(int x) {
    f[x][0] = 0;
    _for(i, 0, son[x].size()) {
        int y = son[x][i];
        dp(y);

        _forDown(t, M, 0) {
            _forDown(j, t, 0) {
                if(t - j < 0) continue;
                f[x][t] = max(f[x][t], f[x][t - j] + f[y][j]);
            }
        }
    }

    if(x) for(int t = M; t > 0; t--) f[x][t] = f[x][t - 1] + score[x];
}

int main() {
    freopen("input.txt", "r", stdin);
    cin >> N >> M;

    _rep(i, 1, N) {
        int x;
        cin >> x >> score[i];
        son[x].push_back(i);
    }

    initdp();
    dp(0);
    cout << f[0][M] << endl;
}