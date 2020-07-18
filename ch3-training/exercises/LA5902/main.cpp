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
int pos[maxn];

void init() {
    Set(pos, 0);
}


class Fwick {
public:
    vector<int> C;
    int n;

    void resize(int n) {
        C.resize(n + 1);
        this->n = n;
    }

    void clear() {
        fill(C.begin(), C.end(), 0);
    }

    int sum(int x) {
        int ret = 0;
        while (x) {
            ret += C[x];
            x -= lowbit(x);
        }
        return ret;
    }

    void add(int x, int d) {
        while (x <= n) {
            C[x] += d;
            x += lowbit(x);
        }
    }
};

Fwick fwick;

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    while (T--) {
        //init();

        scanf("%d%d", &n, &m);

        fwick.resize((maxn + 1) * 2);
        fwick.clear();

        int st = maxn;

        _rep(i, 1, n) {
            pos[i] = st + i;
            fwick.add(pos[i], 1);
        }

        _for(i, 0, m) {
            int x;
            scanf("%d", &x);
            printf("%d%c", fwick.sum(pos[x] - 1), i == m - 1 ? '\n' : ' ');

            fwick.add(pos[x], -1);
            pos[x] = st--;
            fwick.add(pos[x], 1);
        }
    }
}