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

const int maxn = 100 + 5;
const int inf = 0x3f3f3f3f;

struct Node {
    int x;
    char op;
};

Node nodes[maxn];
int Fmax[maxn][maxn], Fmin[maxn][maxn];
int N;

void initdp() {
    Set(Fmax, -inf);
    Set(Fmin, inf);

    _rep(i, 1, (N << 1)) {
        Fmax[i][i] = Fmin[i][i] = nodes[i].x;
        assert(Fmax[i][i] != -inf && Fmin[i][i] != inf);
    }
}

void dp() {
    _rep(len, 2, N) {
        for(int l = 1; l + len - 1 <= (N << 1); l++) {
            int r = l + len - 1;
            _rep(k, l + 1, r) {
                if(nodes[k].op == 't') {
                    // update Fmax and Fmin
                    Fmax[l][r] = max(Fmax[l][r], Fmax[l][k - 1] + Fmax[k][r]);
                    Fmin[l][r] = min(Fmin[l][r], Fmin[l][k - 1] + Fmin[k][r]);
                }
                else {
                    // update Fmax and Fmin, much more complicate
                    Fmax[l][r] = max(Fmax[l][r], max(Fmax[l][k - 1] * Fmax[k][r], Fmin[l][k - 1] * Fmin[k][r]));
                    Fmin[l][r] = min(Fmin[l][r], min(Fmin[l][k - 1] * Fmin[k][r], min(Fmax[l][k - 1] * Fmax[k][r], min(Fmin[l][k - 1] * Fmax[k][r], Fmax[l][k - 1] * Fmin[k][r]))));
                }
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &N);
    _rep(i, 1, N) {
        int x;
        char op;
        cin >> op >> x;
        nodes[i].op = op;
        nodes[i].x = x;
        //debug(nodes[i].x);
    }
    _rep(i, N + 1, (N << 1)) {
        nodes[i] = nodes[i - N];
        assert(nodes[i].x == nodes[i - N].x && nodes[i].op == nodes[i - N].op);
    }

    initdp();
    dp();

    int ans = -inf;
    _rep(i, 1, N) ans = max(ans, Fmax[i][i + N - 1]);
    cout << ans << endl;

    _rep(i, 1, N) if(Fmax[i][i + N - 1] == ans) cout << i << " ";
}