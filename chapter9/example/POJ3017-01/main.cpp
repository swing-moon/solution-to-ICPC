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
llong A[maxn];
int N;
llong M;

multiset<llong> s;
multiset<llong>::iterator it;

llong f[maxn];

void init() {
    s.clear();
    Set(f, 0);
}

void solve() {
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

            if(!que.empty() && (it = s.find(f[t] + A[que.front()])) != s.end()) {
                s.erase(it);
            }
        }
        // == que[front] finished ==
        // == now que[front] is p  ==

        // == Monotonic queue ==
        while (!que.empty() && A[que.back()] <= A[i]) {
            int b = que.back();
            que.pop_back();

            if(!que.empty() && (it = s.find(f[que.back()] + A[b])) != s.end()) {
                s.erase(it);
            }
        }
        // == Monotonic queue finished ==

        if(!que.empty()) s.insert(f[que.back()] + A[i]);
        que.push_back(i);

        f[i] = f[p - 1] + A[que.front()];
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