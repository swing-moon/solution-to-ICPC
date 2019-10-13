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
int S[maxn], st[maxn];
char str[maxn];

int n, L;

void init() {
    Set(S, 0);
    Set(st, 0);
    Set(str, 0);
}

void initCal() {
    S[0] = 0;
    _rep(i, 1, n) S[i] = S[i - 1] + str[i] - '0';
}

int minusSlope(int x1, int x2, int x3, int x4) {
    return (S[x2] - S[x1 - 1]) * (x4 - x3 + 1) - (S[x4] -S[x3 - 1]) * (x2 - x1 + 1);
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);

    while(kase--) {
        init();
        scanf("%d%d%s", &n, &L, str + 1);

        // input finished
        initCal();

        int ansL = 1, ansR = n;
        int l = 0, r = 0;
        _rep(t, L, n) {
            // st[l, r) is candidate start point
            // t - L + 1 represent start point
            // stack st, put value t - L + 1
            while (r - l > 1 && minusSlope(st[r - 2], t - L, st[r - 1], t - L) >= 0) r--;
            st[r++] = t - L + 1;

            // find tangent point st[l]
            // [st[l], t) is the max
            while(r - l > 1 && minusSlope(st[l], t, st[l + 1], t) <= 0) l++;

            int dslp = minusSlope(st[l], t, ansL, ansR);
            if(dslp > 0 || (dslp == 0 && t - st[l] < ansR - ansL)) {
                ansL = st[l];
                ansR = t;
            }
        }
        printf("%d %d\n", ansL, ansR);
    }
}