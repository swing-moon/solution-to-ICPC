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

const int maxm = 200000 + 10;
const int maxn = 100000 + 10;
int n, m;

class Gate {
public:
    int a, b, o;
    void clear() {
        a = b = o = 0;
    }
};
Gate gates[maxm];

void init() {
    _for(i, 0, maxm) gates[i].clear();
}

// k 0's:  00...011...1
// as data flows to gates[1...m]
int output(int k) {
    _rep(i, 1, m) {
        int a = gates[i].a;
        int b = gates[i].b;

        int va = a < 0 ? (-a) > k : gates[a].o;
        int vb = b < 0 ? (-b) > k : gates[b].o;

        gates[i].o = !(va & vb);
    }
    return gates[m].o;
}

int solve(int vn) {
    // vn are all 0
    int L = 1, R = n;
    while(L < R) {
        int M = L + (R - L) / 2;
        if(output(M) == vn) R = M;
        else L = M + 1;
    }
    return L;
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    while(T--) {
        init();
        scanf("%d%d", &n, &m);
        _rep(i, 1, m) scanf("%d%d", &gates[i].a, &gates[i].b);

        // input finished

        // solve gates A = 0
        int v0 = output(0);
        // all 1
        int vn = output(n);
        // all zero
        if(v0 == vn) {
            _rep(i, 1, n) printf("0");
        }
        else {
            //
            int x = solve(vn);
            _for(i, 1, x) printf("0");
            printf("x");
            _rep(i, x + 1, n) printf("1");
        }
        printf("\n");
    }
}