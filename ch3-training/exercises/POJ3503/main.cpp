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

const int maxn = 500 + 5;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
int n, m, d;

class Node {
public:
    int x, y, val;
    Node(int x = 0, int y = 0, int val = 0) : x(x), y(y), val(val) {}

    bool operator< (const Node& rhs) const {
        return val > rhs.val;
    }
};

vector<Node> vec;
int vis[maxn][maxn], G[maxn][maxn];

void init() {
    Set(vis, 0);
    vec.clear();
}

void inp() {
    scanf("%d%d%d", &n, &m, &d);
    _rep(i, 1, n) _rep(j, 1, m) {
        scanf("%d", &G[i][j]);
        vec.push_back(Node(i, j, G[i][j]));
    }
    sort(vec.begin(), vec.end());
}

Node que[maxn * maxn];
int bfs(int x, int y, int h) {
    int front = 0, rear = 1;

    que[front] = Node(x, y);
    int flag = 1, cnt = 1;

    while (front < rear) {
        Node u = que[front];

        _for(dir, 0, 4) {
            int nx = u.x + dx[dir], ny = u.y + dy[dir];

            if(nx <= 0 || nx > n || ny <= 0 || ny > m) continue;
            if(G[nx][ny] <= h - d) continue;

            if(G[nx][ny] > h) {
                flag = 0;
                continue;
            }

            if(vis[nx][ny] == h) continue;
            if(G[nx][ny] == h) cnt++;

            vis[nx][ny] = h;

            que[rear++] = Node(nx, ny);
        }

        front++;
    }

    if(flag == 0) return 0;
    return cnt;
}

int solve() {
    int ans = 0;
    _for(i, 0, vec.size()) {
        int x = vec[i].x, y = vec[i].y;
        if(vis[x][y]) continue;

        vis[x][y] = G[x][y];
        ans += bfs(x, y, G[x][y]);
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    while (T--) {
        init();
        inp();

        // == then bfs and solve ==
        printf("%d\n", solve());
        // == bfs finished ==
    }
}