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

llong tot(int k) {
    return k == 0 ? 1 : 3 * tot(k - 1);
}

llong f(int k, int i) {
    if(i == 0) return 0;
    if(k == 0) return 1;

    int exp = (1 << (k - 1));
    if(i < exp) return 2 * f(k - 1, i);
    else return 2 * tot(k - 1) + f(k - 1, i - exp);
}

int main() {
    freopen("input.txt", "r", stdin);
    int T, k, a, b;
    scanf("%d", &T);
    _rep(kase, 1, T) {
        cin >> k >> a >> b;
        cout << "Case " << kase << ": " << f(k, b) - f(k, a - 1) << "\n";
    }
}