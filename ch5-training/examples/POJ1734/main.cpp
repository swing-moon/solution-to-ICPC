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

const int maxn = 200 + 10;
const int inf = 0x3f3f3f3f;
int n, m;

// == Graph definition ==
int w[maxn][maxn], d[maxn][maxn];
int pos[maxn][maxn];
vector<int> path;

void init() {
    Set(w, inf);
    _rep(i, 0, n) w[i][i] = 0;

    Set(d, 0);
    Set(pos, 0);
    path.clear();
}

// == Graph finsihed ==

// == get path ==
// not include x, y
void getPath(const int x, const int y, vector<int>& path) {
    if(pos[x][y] == 0) return;
    getPath(x, pos[x][y], path);
    path.push_back(pos[x][y]);
    getPath(pos[x][y], y, path);
}
// == get path finished ==

// == floyd ==
int ans = inf;
void initFloyd() {
    Cpy(d, w);
    ans = inf;
}

void floyd() {
    initFloyd();
    _rep(k, 1, n) {
        _for(i, 1, k) _for(j, i + 1, k) {
            if((ll)d[i][j] + w[j][k] + w[k][i] < ans) {
                ans = d[i][j] + w[j][k] + w[k][i];

                path.clear();
                path.push_back(i);
                getPath(i, j, path);
                path.push_back(j);
                path.push_back(k);
            }
        }

        _rep(i, 1, n) _rep(j, 1, n) {
            if(d[i][j] > d[i][k] + d[k][j]) {
                d[i][j] = d[i][k] + d[k][j];
                pos[i][j] = k;
            }
        }
    }
}
// == floyd finsished ==

int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> m;
    init();

    // == build graph ==
    _rep(i, 1, m) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        w[x][y] = w[y][x] = min(w[x][y], z);
    }
    // == build finsiehd ==
    floyd();
    if(ans == inf) {
        puts("No solution.");
        return 0;
    }
    _for(i, 0, path.size()) {
        printf("%d ", path[i]);
    }
    puts("");
}