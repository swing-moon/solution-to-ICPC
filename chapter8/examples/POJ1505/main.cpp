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

const int maxn = 500 + 10;
int A[maxn], m, k;
int last[maxn];
llong tot = 0;
int maxv = -1;

void init() {
    Set(A, 0);
    Set(last, 0);
    tot = 0;
    maxv = -1;
}

int solve(llong x) {
    llong ans = 0;
    // do not exceed x
    int cnt = 1;
    _for(i, 0, m) {
        if(ans + A[i] <= x) ans += A[i];
        else {
            ans = A[i];
            cnt++;
        }
    }
    return cnt;
}

void print(llong x) {
    // do not exceed x
    llong ans = 0;
    int remain = k;
    _forDown(i, m - 1, 0) {
        if(ans + A[i] > x || i + 1 < remain) {
            last[i] = 1;
            remain--;
            ans = A[i];
        }
        else ans += A[i];
    }
    _for(i, 0, m-1) {
        printf("%d ", A[i]);
        if(last[i]) printf("/ ");
    }
    printf("%d\n", A[m - 1]);
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);

    while(kase--) {
        init();
        scanf("%d%d", &m, &k);
        _for(i, 0, m) {
            scanf("%d", &A[i]);
            tot += A[i];
            maxv = max(maxv, A[i]);
        }
        // then we finished input
        // binary search
        llong L = maxv, R = tot;
        while(L < R) {
            llong mid = L + (R - L) / 2;
            if(solve(mid) <= k) R = mid;
            else L = mid + 1;
        }
        print(L);
    }
}