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

const int maxn = 6 + 3;
const int maxm = 20000 + 5;
const int N = 6;

bitset<maxm> f;
int A[maxn];

void initdp() {
    f &= 1;
    f[0] = 1;
}

bool dp() {
    int totV = 0;
    _rep(x, 1, 6) totV += x * A[x];

    if(totV & 1) return false;
    else totV /= 2;

    _rep(i, 1, N) {
        // value is i
        for(int p = 1; p <= A[i]; p <<= 1) {
            f |= (f << (p * i));
            A[i] -= p;
        }
        if(A[i]) f |= (f << (A[i] * i));
    }

    if(f[totV]) return true;
    else return false;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (1) {
        int finished = true;
        _rep(i, 1, N) scanf("%d", &A[i]);

        _rep(i, 1, N) if(A[i] != 0) finished = false;
        if(finished) return 0;

        initdp();
        bool flag = dp();

        if(flag) puts("Can");
        else puts("Can't");
    }
}