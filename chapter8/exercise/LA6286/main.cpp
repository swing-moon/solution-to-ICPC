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

int A[4];
int cur;

void init() {
    Set(A, 0);
    cur = 0;
}

void move(int step) {
    int id = abs(step);
    cur += step;
    printf(" %d", cur);
    A[id]--;
}

void move(int step, int cnt) {
    _for(i, 0, cnt) move(step);
}

void solve() {
    printf("0");

    int cnt3 = A[3] / 3;
    int n = A[3] % 3;

    if(n == 0) {
        move(3, cnt3);
        move(1);

        move(-3, cnt3);
        move(1);

        move(3, cnt3);
    }
    if(n == 1) {
        move(3, cnt3 + 1);
        move(-2);

        move(-3, cnt3);
        move(1);

        move(3, cnt3);
        move(2);
    }
    if(n == 2) {
        move(3, cnt3 + 1);
        move(-1);

        move(-3, cnt3);
        move(-1);

        move(3, cnt3 + 1);
    }


    move(1, A[1] - 1);

    int cnt2 = A[2] / 2, n2 = A[2] % 2;

    if(n2 == 0) {
        move(2, cnt2);
        move(1);
        move(-2, cnt2);
    }
    if(n2 == 1) {
        move(2, cnt2 + 1);
        move(-1);
        move(-2, cnt2);
    }

    puts("");
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    while(scanf("%d", &T) == 1) {
        while (T--) {
            init();
            scanf("%d%d%d", &A[1], &A[2], &A[3]);
            solve();
        }
    }
}