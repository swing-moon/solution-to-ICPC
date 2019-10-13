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

const int maxn = 200000 + 10;

inline int lowbit(int x) {
    return x & (-x);
}

int cnt1[maxn], cnt2[maxn];
int A[maxn];

void init() {
    Set(cnt1, 0);
    Set(cnt2, 0);
}

class Fenwick {
public:
    vector<int> exist;
    int n;

    void clear() {
        fill(exist.begin(), exist.end(), 0);
    }

    void resize(int n) {
        this->n = n;
        exist.resize(n);
    }

    int sum(int x) {
        int ret = 0;
        while (x > 0) {
            ret += exist[x];
            x -= lowbit(x);
        }
        return ret;
    }

    void add(int x, int d) {
        while (x <= n) {
            exist[x] += d;
            x += lowbit(x);
        }
    }
};

Fenwick fwick;

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    while (T--) {
        init();
        int maxa = 0;
        int n;
        scanf("%d", &n);
        _rep(i, 1, n) {
            scanf("%d", &A[i]);
            maxa = max(maxa, A[i]);
        }

        fwick.resize(maxa);
        fwick.clear();

        _rep(i, 1, n) {
            int val = A[i];
            fwick.add(val, 1);
            cnt1[i] = fwick.sum(val - 1);
        }

        fwick.clear();
        _forDown(i, n, 1) {
            int val = A[i];
            fwick.add(val, 1);
            cnt2[i] = fwick.sum(val - 1);
            //debug(cnt2[i]);
        }

        llong ans = 0;
        _rep(i, 1, n) {
            ans += ((llong)cnt2[i] * (llong)(i - 1 - cnt1[i]) + (llong)cnt1[i] * (llong)(n - i - cnt2[i]));
        }
        printf("%lld\n", ans);
    }
}