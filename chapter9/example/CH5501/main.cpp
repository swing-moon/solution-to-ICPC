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

const int maxn = 2000000 + 5;
int A[maxn], ans = 0;
int N;

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &N);
    _rep(i, 1, N) scanf("%d", &A[i]);
    _rep(i, N + 1, (N << 1)) A[i] = A[i - N];

    deque<int> dq;
    dq.push_front(1);
    _rep(i, 2, (N << 1)) {
        while (!dq.empty() && dq.back() < i - N / 2) dq.pop_back();
        ans = max(ans, A[i] + A[dq.back()] + i - dq.back());
        while (!dq.empty() && A[i] - i >= A[dq.front()] - dq.front()) dq.pop_front();
        dq.push_front(i);
    }
    printf("%d\n", ans);
}