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

const int maxn = 20000 + 10;
const int maxm = 100000 + 10;
int pa[maxn * 2];
int n, m;

void initPa(int n) {
    _rep(i, 0,n) pa[i] = i;
}
// usage initPa(n * 2);

class Cfl {
public:
    int x, y, val;

    bool operator< (const Cfl& rhs) const {
        return val > rhs.val;
    }
};

Cfl cfl[maxm];

int find(int x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);


    _for(i, 0, m) {
        scanf("%d%d%d", &cfl[i].x, &cfl[i].y, &cfl[i].val);
    }

    initPa(n * 2);

    sort(cfl, cfl + m);

    _for(i, 0, m) {
        Cfl& cur = cfl[i];
        //debug(cur.x);
        if(find(cur.x) == find(cur.y)) {
            printf("%d\n", cur.val);
            return 0;
        }
        pa[find(cur.x)] = find(cur.y + n);
        pa[find(cur.y)] = find(cur.x + n);
    }
    printf("0\n");
    return 0;
}