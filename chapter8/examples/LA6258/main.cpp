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

const int maxn = 200000 + 5;
int pre[maxn], nxt[maxn], A[maxn];
map<int, int> cur;
int n;

void initCur() {
    cur.clear();
}

void init() {
    Set(pre, 0);
    Set(nxt, 0);
    Set(A, 0);
}

inline bool uniq(int p, int L, int R) {
    return pre[p] < L && nxt[p] > R;
}

bool check(int L, int R) {
    if(L >= R) return true;

    for(int d = 0; L + d <= R - d; d++) {
        if(uniq(L + d, L, R)) return check(L, L + d - 1) && check(L + d + 1, R);
        if(L + d == R - d) break;
        if(uniq(R - d, L, R)) return check(L, R - d - 1) && check(R - d + 1, R);
    }
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    while (T--) {
        // init();
        initCur();

        scanf("%d", &n);
        _for(i, 0, n) {
            scanf("%d", &A[i]);
            if(!cur.count(A[i])) pre[i] = -1;
            else pre[i] = cur[A[i]];
            cur[A[i]] = i;
        }

        initCur();
        _forDown(i, n - 1, 0) {
            if(!cur.count(A[i])) nxt[i] = n;
            else nxt[i] = cur[A[i]];
            cur[A[i]] = i;
        }

        if(check(0, n - 1)) printf("non-boring\n");
        else printf("boring\n");
    }
}