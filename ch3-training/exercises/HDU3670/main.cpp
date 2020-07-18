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

const int maxn = 100000 + 10;
const int mod = 1<<16;
const int maxm = mod + 10;
int cas = 0;

int n, m;

class Fwick {
public:
    int C[16][maxm];

    void init() {
        Set(C, 0);
    }

    void update(int k, int x, int d) {
        x++;
        while (x < maxm) {
            C[k][x] += d;
            x += lowbit(x);
        }
    }

    int sum(int k, int x) {
        x++;
        int ret = 0;
        while (x) {
            ret += C[k][x];
            x -= lowbit(x);
        }
        return ret;
    }
} fwick;

void solve() {
    ll add = 0, ans = 0;
    char cmd[10];

    while (scanf("%s", cmd) == 1) {
        if(cmd[0] == 'E') break;

        if(cmd[0] == 'C') {
            int x;
            scanf("%d", &x);
            add += x;
            if(add >= mod) add %= mod;
        }
        else {
            int t;
            scanf("%d", &t);
            int tail = add % (1<<t);

            if(add & (1<<t)) {
                ans += fwick.sum(t, (1<<t) - 1- tail);
                ans += fwick.sum(t, (1<<(t+1)) - 1) - fwick.sum(t, (1<<(t+1)) - 1 - tail);
            }
            else {
                ans += fwick.sum(t, (1<<(t+1)) - 1 - tail) - fwick.sum(t, (1<<t) - 1 - tail);
            }
        }
    }
    printf("Case %d: %lld\n", ++cas, ans);
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &n) == 1) {
        if(n == -1) break;
        fwick.init();

        _for(i, 0, n) {
            int x;
            scanf("%d", &x);
            _for(k, 0, 16) fwick.update(k, x % (1<<(k+1)), 1);
        }

        // then solve the problem
        solve();
    }
}