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

const int maxn = 100000 + 10;

class Con {
public:
    int i, j;
    int e;
};

Con cons[maxn];
int n;

int pa[maxn * 2];
int arr[maxn * 2];

void init() {
    _for(i, 0, maxn) pa[i] = i;
    Set(arr, 0);
}

int find(int x) {
    return x == pa[x] ? x : (pa[x] = find(pa[x]));
}

void discrete(int* arr, int m, int& n) {
    sort(arr, arr + m);
    n = unique(arr, arr + m) - arr;
}

int query(int* arr, int n, int x) {
    return lower_bound(arr, arr + n, x) - arr;
}

void solve() {
    int m = n * 2;
    int n2 = 0;
    discrete(arr, m, n2);

    _rep(i, 0, n2) pa[i] = i;

    _for(i, 0, n) {
        int p = find(query(arr, n2, cons[i].i)), q = find(query(arr, n2, cons[i].j));
        if(cons[i].e) pa[p] = q;
    }

    _for(i, 0, n) {
        int p = find(query(arr, n2, cons[i].i)), q = find(query(arr, n2, cons[i].j));
        if(!cons[i].e && p == q) {
            printf("NO\n");
            return;
        }
    }
    printf("YES\n");
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    while (T--) {
        init();

        scanf("%d", &n);
        _for(i, 0, n) {
            scanf("%d%d%d", &cons[i].i, &cons[i].j, &cons[i].e);

            arr[i * 2] = cons[i].i;
            arr[i * 2 + 1] = cons[i].j;
        }

        // then solve the problem
        solve();

    }
}