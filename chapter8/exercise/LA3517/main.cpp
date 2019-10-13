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
int n;

llong L[maxn], R[maxn], sum[maxn], A[maxn];
stack<int> stk;
// stk used to store index

void init() {
    Set(sum, 0);
    Set(A, 0);
    Set(L, 0);
    Set(R, 0);
}

void popGreater(int i) {
    while(!stk.empty() && A[stk.top()] >= A[i]) stk.pop();
}

void solve() {
    while (!stk.empty()) stk.pop();

    _rep(i, 1, n) {
        popGreater(i);
        L[i] = stk.empty() ? 0 : stk.top();
        stk.push(i);
    }

    while (!stk.empty()) stk.pop();

    _forDown(i, n, 1) {
        popGreater(i);
        R[i] = stk.empty() ? n + 1 : stk.top();
        stk.push(i);
    }

    llong ans = -1, ansl = -1, ansr = -1;
    _rep(i, 1, n) {
        // if A[i] is min value
        llong li = L[i], ri = R[i] - 1, tmp = (sum[ri] - sum[li]) * A[i];
        li++;

        bool update = false;
        if(tmp < ans) continue;
        if(tmp > ans) update = true;

        if(tmp == ans) {
            if(ansr - ansl > ri - li) update = true;
            else if(ansr - ansl == ri - li) update = li < ansl;
        }

        ans = max(tmp, ans);
        if(update) {
            ansl = li;
            ansr = ri;
        }
    }

    printf("%lld\n%lld %lld\n", ans, ansl, ansr);
}


int main() {
    freopen("input.txt", "r", stdin);

    bool first = true;

    while (scanf("%d", &n) == 1) {
        init();

        if(first) first = false;
        else puts("");


        bool all0 = true;
        _rep(i, 1, n) {
            scanf("%lld", &A[i]);
            if(A[i]) all0 = false;
            sum[i] = A[i] + sum[i - 1];
        }


        if(all0) {
            printf("0\n1 1\n");
            continue;
        }

        // then solve the problem
        solve();
    }
}