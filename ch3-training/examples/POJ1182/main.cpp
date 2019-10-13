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

const int maxn = 50000 + 10;

int pa[maxn * 3];
int n, k;

// usage: initPa(n * 3)
void initPa(int n) {
    _rep(i, 0, n) pa[i] = i;
}

int find(int x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}

// x: self   x + n: eat   x + 2n: enemy

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &k);

    initPa(n * 3);
    int ans = 0;

    _for(i, 0, k) {
        int cmd, x, y;
        scanf("%d%d%d", &cmd, &x, &y);

        if(cmd == 2 && (x == y)) {
            ans++;
            continue;
        }

        if(x > n || y > n) {
            ans++;
            continue;
        }

        if(cmd == 1) {
            //
            if((find(x + n) == find(y)) || (find(x) == find(y + n))) {
                ans++;
                continue;
            }
        }
        if(cmd == 2) {
            //
            if((find(x) == find(y)) || (find(x) == find(y + n))) {
                ans++;
                continue;
            }
        }

        if(cmd == 1) {
            //
            pa[find(x)] = find(y);
            pa[find(x + n)] = find(y + n);
            pa[find(x + n * 2)] = find(y + n * 2);
        }
        else if(cmd == 2) {
            //
            pa[find(x)] = find(y + n * 2);
            pa[find(x + n)] = find(y);
            pa[find(x + n * 2)] = find(y + n);
        }
    }

    cout << ans << endl;
}