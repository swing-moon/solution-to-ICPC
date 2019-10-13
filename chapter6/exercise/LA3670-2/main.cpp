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

const int maxn = 24;
int grid[maxn][maxn];
int vis[maxn][maxn];

void init() {
    Set(grid, 0);
    Set(vis, 0);
}
int n, m, k;

struct Node {
    int x, y, dist, obs;
    Node(int _x, int _y, int _d, int _o) : x(_x), y(_y), dist(_d), obs(_o) {}
};

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

bool valid(int x, int y) {
    return 0 <= x && x < m && 0 <= y && y < n;
}

int bfs() {
    queue<Node> que;
    que.push(Node(0, 0, 1, 0));

    while (!que.empty()) {
        Node f = que.front();
        que.pop();
        vis[f.x][f.y] = 1;

        if(f.x == m - 1 && f.y == n - 1) return f.dist - 1;

        _for(dir, 0, 4) {
            int nx = f.x + dx[dir], ny = f.y + dy[dir];
            if(!valid(nx, ny)) continue;
            if(vis[nx][ny]) continue;

            if(grid[nx][ny] == 0) que.push(Node(nx, ny, f.dist + 1, 0));
            else {
                if(f.obs + 1 <= k) que.push(Node(nx, ny, f.dist + 1, f.obs + 1));
            }
        }
    }
    return -1;
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    while (T--) {
        init();
        scanf("%d%d%d", &m, &n, &k);
        _for(i, 0, m) _for(j, 0, n) scanf("%d", &(grid[i][j]));

        printf("%d\n", bfs());
    }
}