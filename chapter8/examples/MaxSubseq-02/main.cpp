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

const int maxn = 300000 + 10;
int A[maxn];
llong S[maxn];
int n, m;
deque<int> que;

void init() {
    Set(A, 0);
    Set(S, 0);
    while(!que.empty()) que.pop_front();
}

int main() {
    freopen("input.txt", "r", stdin);
    init();

    cin >> n >> m;
    _rep(i, 1, n) {
        scanf("%d", &A[i]);
        S[i] = S[i - 1] + A[i];
    }

    llong ans = 0;
    // use [que.back(), que.front()] to match [i - m, i - 1]
    // ans = max(ans, [que.back(), i])

    que.push_front(0);
    _rep(i, 1, n) {
        while(!que.empty() && que.back() < i - m) que.pop_back();
        ans = max(ans, S[i] - S[que.back()]);
        while(!que.empty() && S[que.front()] >= S[i]) que.pop_front();
        que.push_front(i);
    }
    cout << ans << endl;
}