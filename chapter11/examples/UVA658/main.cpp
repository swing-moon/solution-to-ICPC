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
typedef long long ll;
typedef set<int>::iterator ssii;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
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

const int maxn = 20;
const int maxm = 100 + 5;
const int inf = 0x3f3f3f3f;
int T[maxm];
int n, m;

// == node definition ==
class Node {
public:
    int state, dist;
    bool operator< (const Node& rhs) const {
        return dist > rhs.dist;
    }
    Node() {}
    Node(int s, int d) : state(s), dist(d) {}
};

int D[1<<maxn], vis[1<<maxn];
char before[maxm][maxn], after[maxm][maxn];

void initG() {
    Set(D, inf);
    Set(vis, 0);
}
// == node finished ==

// == Dijkstra ==
bool valid(const Node& u, const int k) {
    // check before patches k
    _for(i, 0, n) {
        if(before[k][i] == '-' && ((1<<i) & u.state)) return false;
        if(before[k][i] == '+' && !((1<<i) & u.state)) return false;
    }
    return true;
}

int dijkstra() {
    priority_queue<Node> que;
    Node st((1<<n)-1, 0);
    que.push(st);
    D[st.state] = 0;

    while (!que.empty()) {
        Node x = que.top(); que.pop();
        if(x.state == 0) return D[x.state];
        if(vis[x.state]) continue;
        vis[x.state] = 1;

        // get next y
        _rep(i, 1, m) {
            bool patchable = valid(x, i);
            if(!patchable) continue;

            // use patches i
            Node y(x.state, x.dist + T[i]);
            _for(j, 0, n) {
                if(after[i][j] == '+') y.state |= (1<<j);
                if(after[i][j] == '-') y.state &= ~(1<<j);
            }

            if(D[y.state] > y.dist) {
                D[y.state] = y.dist;
                que.push(y);
            }
        }
    }
    return -1;
}
// == Dijkstra finsihed ==

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;
    while (scanf("%d%d", &n, &m) == 2 && n) {
        initG();
        _rep(i, 1, m) scanf("%d%s%s", &T[i], before[i], after[i]);
        printf("Product %d\n", ++kase);

        // then solve the problem
        int ans = dijkstra();
        if(ans < 0) printf("Bugs cannot be fixed.\n\n");
        else printf("Fastest sequence takes %d seconds.\n\n", ans);
    }
}