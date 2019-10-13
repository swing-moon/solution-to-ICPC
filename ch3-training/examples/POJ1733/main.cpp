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

const int maxn = 10000 + 10;

struct Query {
    int l, r, ans;
};
Query query[maxn];

void discrete(int* arr, int n, int& n2) {
    sort(arr + 1, arr + 1 + n);
    n2 = unique(arr + 1, arr + 1 + n) - arr - 1;
}

int getid(int* arr, int n2, int x) {
    return lower_bound(arr + 1, arr + 1 + n2, x) - arr;
}

int arr[maxn], n, m;
int pa[maxn], d[maxn];

void init() {
    Set(arr, 0);
}

void initPa(int n) {
    _rep(i, 0, n) pa[i] = i;
    _rep(i, 0, n) d[i] = 0;
}

int find(int x) {
    if(x == pa[x]) return x;
    int root = find(pa[x]);

    d[x] ^= d[pa[x]];
    return pa[x] = root;
}


int main() {
    freopen("input.txt", "r", stdin);
    std::ios::sync_with_stdio(false);

    cin >> n >> m;

    int k = 0;
    _rep(i, 1, m) {
        char str[5];
        cin >> query[i].l >> query[i].r;

        scanf("%s", str);
        if(str[0] == 'o') query[i].ans = 1;
        else query[i].ans = 0;

        arr[++k] = query[i].l - 1;
        arr[++k] = query[i].r;
    }
    discrete(arr, k, n);
    //debug(n);
    // [0, m - 1] is all query

    initPa(n);
    _rep(i, 1, m) {
        int x = getid(arr, n, query[i].l - 1);
        int y = getid(arr, n, query[i].r);
        int p = find(x), q = find(y);

        if(p == q) {
            //
            if( (d[x] ^ d[y]) != query[i].ans ) {
                cout << i - 1 << endl;
                return 0;
            }
        }
        else {
            pa[p] = q;
            d[p] = d[x] ^ d[y] ^ query[i].ans;
        }
    }
    cout << m << endl;
    return 0;
}