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
#define MPR(a, b) make_pair(a, b)

const int maxn = 100006;
const int maxt = 30;
llong A[maxn], M;
int N;

multiset<llong> s;
multiset<llong>::iterator it;

llong f[maxn], Q[maxn][maxt];

// == ST Algorithm ==
void ST() {
    _rep(i, 1, N) Q[i][0] = A[i];
    int t = log(N) / log(2) + 1;
    _for(k, 1, t) _rep(i, 1, N - (1<<k) + 1) {
            Q[i][k] = max(Q[i][k - 1], Q[i + (1 << (k - 1))][k - 1]);
        }
}

llong ask(int l, int r) {
    int k = log(r - l + 1) / log(2);
    return max(Q[l][k], Q[r - (1<<k) + 1][k]);
}
// == ST Algorithm finished ==

void init() {
    Set(f, 0);
    Set(Q, 0);
    s.clear();
}

void solve() {
    ST();
    deque<int> que;
    llong sum = 0;
    int p = 1;

    _rep(i, 1, N) {
        sum += A[i];
        while (sum > M) sum -= A[p++];

        // == get que[front] ==
        while (!que.empty() && que.front() < p) {
            int t = que.front();
            que.pop_front();

            if(!que.empty() && (it = s.find(f[t] + A[que.front()])) != s.end()) s.erase(it);
        }
        // == que[front] finished, now que[front] = p

        // == Monotonic queue ==
        while (!que.empty() && A[que.back()] <= A[i]) {
            int b = que.back();
            que.pop_back();

            if(!que.empty() && (it = s.find(f[que.back()] + A[b])) != s.end()) s.erase(it);
        }

        if(!que.empty()) s.insert(f[que.back()] + A[i]);
        que.push_back(i);
        // == Monotonic queue finished ==

        f[i] = f[p - 1] + ask(p, i);
        if(s.begin() != s.end()) f[i] = min(f[i], *s.begin());
    }
    cout << f[N] << endl;
}


int main() {
    freopen("input.txt", "r", stdin);
    cin >> N >> M;

    // == input ==
    _rep(i, 1, N) {
        scanf("%lld", &A[i]);
        if(A[i] > M) {
            puts("-1");
            return 0;
        }
    }
    // == input finished ==

    solve();
}