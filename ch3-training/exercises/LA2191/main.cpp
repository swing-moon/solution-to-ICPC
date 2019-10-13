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
int A[maxn];
int n;

class Fwick {
public:
    vector<int> C;
    int n;

    void resize(int n) {
        this->n = n;
        C.resize(n + 1);;
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

void init() {
    Set(A, 0);
    fwick.resize(n);
    fwick.clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;

    while (scanf("%d", &n) && n) {
        init();
        if(kase) puts("");
        printf("Case %d:\n", ++kase);

        _rep(i, 1, n) {
            scanf("%d", &A[i]);
            fwick.add(i, A[i]);
        }

        char ch[4];
        while (scanf("%s", ch)) {
            if(ch[0] == 'E') break;

            int x, y;
            scanf("%d%d", &x, &y);

            if(ch[0] == 'S') {
                //
                fwick.add(x, -A[x] + y);
                A[x] = y;
            }
            else {
                //
                int ans = fwick.sum(y) - fwick.sum(x - 1);
                printf("%d\n", ans);
            }
        }
    }
}