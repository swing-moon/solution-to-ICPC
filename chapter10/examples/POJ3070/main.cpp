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
typedef long long ll;
typedef set<int>::iterator ssii;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
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
#define MPR(a, b) make_pair(a, b)

const int mod = 10000;
int n;
const int K = 2;

void mul(int f[K], int A[K][K]) {
    int c[K];
    Set(c, 0);

    _for(j, 0, K) _for(k, 0, K) {
        c[j] = (c[j] + (ll)f[k] * A[k][j]) % mod;
    }
    Cpy(f, c);
}

void mulself(int A[K][K]) {
    int c[K][K];
    Set(c, 0);
    _for(i, 0, K) _for(j, 0, K) _for(k, 0, K) {
        c[i][j] = (c[i][j] + (ll)(A[i][k]) * A[k][j]) % mod;
    }
    Cpy(A, c);
}

int main() {
    freopen("input.txt", "r", stdin);
    while (cin >> n && n != -1) {
        int f[2] = {0, 1};
        int A[2][2] = {{0, 1}, {1, 1}};

        for(; n; n >>= 1) {
            if(n & 1) mul(f, A);
            mulself(A);
        }
        cout << f[0] << endl;
    }
}