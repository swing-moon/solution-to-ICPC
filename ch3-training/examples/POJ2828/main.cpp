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

const int maxn = 200000 + 10;
int n;

class Peo {
public:
    int p, v;
};

Peo peo[maxn];
int ans[maxn];

void init() {
    Set(ans, 0);
}

class Fwick {
public:
    vector<int> C;
    int n;

    void resize(int n) {
        this->n = n;
        C.resize(n);
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

    int find(int l, int r, int val) {
        while (l < r) {
            int mid = (l + r) >> 1;
            if(sum(mid) < val) l = mid + 1;
            else r = mid;
        }
        return l;
    }
};

Fwick fwick;


int main() {
    freopen("input.txt", "r", stdin);
    while (~scanf("%d", &n)) {
        //debug(n);
        init();
        fwick.resize(n);
        fwick.clear();

        _rep(i, 1, n) {
            //debug(i);
            scanf("%d%d", &peo[i].p, &peo[i].v);
            //debug(peo[i].p);
            //debug(peo[i].v);
            fwick.add(i, 1);
        }

        _forDown(i, n, 1) {
            int val = peo[i].p;
            int pos = fwick.find(1, n, val + 1);
            //debug(pos);

            ans[pos] = peo[i].v;
            fwick.add(pos, -1);

            //debug(peo[i].v);
        }
        _rep(i, 1, n) {
            if(i != n) printf("%d ", ans[i]);
            else printf("%d\n", ans[i]);
        }
    }
}