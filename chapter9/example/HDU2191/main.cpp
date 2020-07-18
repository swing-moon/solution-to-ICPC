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

const int inf = 0xcf;
const int maxn = 20000 + 10;
int n, m;

int f[maxn];
int W[maxn], V[maxn], C[maxn];

void init() {
    Set(f, inf);
    f[0] = 0;
}

inline int g(int i, int u, int k) {
    return f[u + k * V[i]] - k * W[i];
}

void solve() {
    init();

    _rep(i, 1, n) {
        scanf("%d%d%d", &V[i], &W[i], &C[i]);
        _for(u, 0, V[i]) {
            deque<int> que;

            // == status variable p ==
            int maxp = (m - u) / V[i];
            _forDown(k, maxp - 1, max(0, maxp - C[i])) {
                while (!que.empty() && g(i, u, que.back()) <= g(i, u, k)) que.pop_back();
                que.push_back(k);
            }

            _forDown(p, maxp, 0) {
                // == compare que.front and p-1
                while (!que.empty() && que.front() > p - 1) que.pop_front();
                if(!que.empty()) f[u + p * V[i]] = max(f[u + p * V[i]], g(i, u, que.front()) + p * W[i]);

                // == compare que.back and maintain monotonic queue
                if(p - 1 - C[i] >= 0) {
                    int k2 = p - 1 - C[i];
                    while (!que.empty() && g(i, u, que.back()) <= g(i, u, k2)) que.pop_back();
                    que.push_back(k2);
                }
            }
            // == status variable finished ==
        }
    }
    int ans = 0;
    _rep(i, 1, m) ans = max(ans, f[i]);
    cout << ans << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d", &m, &n);
        solve();
    }
}