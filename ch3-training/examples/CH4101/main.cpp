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

const int maxn = 30000 + 1;
int pa[maxn];
int d[maxn];
int sz[maxn];

void init() {
    _for(i, 0, maxn) sz[i] = 1;
    _for(i, 0, maxn) d[i] = 0;
}

void initPa(int n) {
    _rep(i, 0, n) pa[i] = i;
}

int find(int x) {
    if(x == pa[x]) return x;
    int root = find(pa[x]);
    d[x] += d[pa[x]];
    return pa[x] = root;
}

void Union(int p, int q) {
    pa[p] = q;
    d[p] = sz[q];
    sz[q] += sz[p];
}

int main() {
    std::ios::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    int T;
    cin >> T;

    initPa(maxn);
    init();
    while (T--) {
        char cmd;
        cin >> cmd;

        int i, j;
        cin >> i >> j;
        //debug(i);
        //debug(j);

        int p = find(i), q = find(j);
        //debug(p);
        //debug(q);

        if(cmd == 'C') {
            //
            if(p == q) cout << abs(d[i] - d[j]) - 1 << endl;
            else cout << "-1" << endl;
        }
        else {
            //
            Union(p, q);
        }
    }
}