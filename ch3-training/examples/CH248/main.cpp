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

const int maxm = 100000 + 10;
const int maxn = 100000 + 10;
int n, m;

llong A[maxn];

void init() {
    Set(A, 0);
}

class Fenwick {
public:
    int n;
    vector<int> h;

    void resize(int n) {
        this->n = n;
        h.resize(n);
    }

    void clear() {
        fill(h.begin(), h.end(), 0);
    }

    int sum(int x) {
        int ret = 0;
        while (x) {
            ret += h[x];
            x -= lowbit(x);
        }
        return ret;
    }

    void add(int x, int d) {
        while (x <= n) {
            h[x] += d;
            x += lowbit(x);
        }
    }
};

Fenwick fwick;

int main() {
    freopen("input.txt", "r", stdin);
    init();
    cin >> n >> m;

    _rep(i, 1, n) cin >> A[i];
    //debug(A[n]);

    //fflush(stdin);
    fwick.clear();
    fwick.resize(maxn);

    //getchar();
    _for(i, 0, m) {
        char ch;
        cin >> ch;
        //debug(ch);
        if(ch == 'C') {
            //
            int l, r, d;
            cin >> l >> r >> d;
            //debug(l);

            fwick.add(l, d);
            fwick.add(r + 1, -d);
        }
        else {
            //
            int x;
            cin >> x;
            cout << A[x] + (llong)fwick.sum(x) << endl;
        }
    }
}