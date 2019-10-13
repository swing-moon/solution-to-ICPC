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

const int maxn = 100000 + 10;
int n, m;
int A[maxn];
llong sum[maxn];

void init() {
    Set(A, 0);
    Set(sum, 0);
}

class Fwick {
public:
    llong C[2][maxn];
    int n;

    void clear() {
        memset(C, 0, sizeof(C));
    }

    void resize(int n) {
        this->n = n;
    }

    llong ask(int k, int x) {
        llong ret = 0;
        while (x) {
            ret += C[k][x];
            x -= lowbit(x);
        }
        return ret;
    }

    void add(int k, int x, int d) {
        while (x <= n) {
            C[k][x] += d;
            x += lowbit(x);
        }
    }
};

Fwick fwick;

int main() {
    freopen("input.txt", "r", stdin);
    init();

    scanf("%d%d", &n, &m);
    _rep(i, 1, n) {
        scanf("%d", &A[i]);
        sum[i] = sum[i - 1] + A[i];
    }

    fwick.clear();
    fwick.resize(n);

    _for(i, 0, m) {
        char op[2];
        scanf("%s", op);

        if(op[0] == 'C') {
            //
            int l, r, d;
            scanf("%d%d%d", &l, &r, &d);

            fwick.add(0, l, d);
            fwick.add(0, r + 1, -d);

            fwick.add(1, l, l * d);
            fwick.add(1, r + 1, -(r + 1) * d);
        }
        else {
            //
            int l, r;
            scanf("%d%d", &l, &r);
            llong ans = sum[r] + (r + 1) * fwick.ask(0, r) - fwick.ask(1, r);
            ans -= (sum[l - 1] + l * fwick.ask(0, l - 1) - fwick.ask(1, l - 1));
            printf("%lld\n", ans);
        }
    }
}