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

class Fenwick {
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
        while (x > 0) {
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

Fenwick fwick;
int n;
int A[maxn], cntl[maxn], cntr[maxn];

void init() {
    Set(A, 0);
    Set(cntl, 0);
    Set(cntr, 0);
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    init();

    int maxa = 0;
    _rep(i, 1, n) {
        scanf("%d", &A[i]);
        maxa = max(maxa, A[i]);
    }

    fwick.clear();
    fwick.resize(maxa);

    _forDown(i, n, 1) {
        int val = A[i];
        fwick.add(val, 1);
        cntr[i] = fwick.sum(val - 1);
    }

    fwick.clear();

    _for(i, 1, n) {
        int val = A[i];
        fwick.add(val, 1);
        cntl[i] = fwick.sum(val - 1);
    }

    llong ans1 = 0, ans2 = 0;
    _for(i, 1, n) {
        ans1 += (llong)(n - i - cntr[i]) * (llong)(i - 1 - cntl[i]);
    }
    cout << ans1 << " ";

    _for(i, 1, n) {
        ans2 += (llong)(cntr[i]) * (llong)(cntl[i]);
    }
    cout << ans2 << endl;
}