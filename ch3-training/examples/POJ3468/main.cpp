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
typedef long long ll;

const int maxn = 100000 + 10;
int n, m;
ll A[maxn];

// == fenwick definition ==
class Fwick {
public:
    vector<ll> C[2];
    int n;

    void resize(int n) {
        this->n = n;
        _for(i, 0, 2) C[i].resize(n + 1);
    }

    void clear() {
        _for(i, 0, 2) fill(C[i].begin(), C[i].end(), 0ll);
    }

    void add(int k, int x, ll d) {
        int i = x;
        for(; i <= n; i += lowbit(i)) C[k][i] += 1ll * d;
    }

    ll ask(int k, int x) {
        ll ans = 0;
        for(int i = x; i; i -= lowbit(i)) ans += C[k][i];
        return ans;
    }

} fwick;
// == fenwick finsihed ==

ll prefix(int x) {
    return fwick.ask(0, x) * (x + 1) - fwick.ask(1, x);
}

void init() {
    fwick.resize(maxn);
    fwick.clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init();

    _rep(i, 1, n) {
        scanf("%lld", &A[i]);
        fwick.add(0, i, A[i] - A[i - 1]);
        fwick.add(1, i, i * (A[i] - A[i - 1]));
    }

    // then solve
    while (m--) {
        char cmd[2];
        scanf("%s", cmd);
        if(cmd[0] == 'C') {
            int l, r, d;
            scanf("%d%d%d", &l, &r, &d);

            fwick.add(0, r + 1, -1ll * d);
            fwick.add(0, l, 1ll * d);

            fwick.add(1, r + 1, -1ll * d * (r + 1));
            fwick.add(1, l, 1ll * d * l);
        }
        else {
            int l, r;
            scanf("%d%d", &l, &r);

            ll ans = prefix(r) - prefix(l - 1);
            printf("%lld\n", ans);
        }
    }
}