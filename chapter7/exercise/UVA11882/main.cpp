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
#include <unordered_set>

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

const int maxr = 15 + 10;
const int maxc = 15 + 10;

int R, C;

int walked[maxr][maxc];
int vis[maxr][maxc];

void initWalk() {
    Set(walked, 0);
}

void initVis() {
    Set(vis, 0);
}

char grid[maxr][maxc];
void init() {
    Set(grid, 0);
}

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};


bool valid(int x, int y) {
    return 0 <= x && x < R && 0 <= y && y < C && isdigit(grid[x][y]);
}

void dbg() {
    _for(i, 0, R) {
        _for(j, 0, C) printf("%c", grid[i][j]);
        printf("\n");
    }
}

class Data {
public:
    vector<char> buf;

    bool operator< (const Data& rhs) const {
        if(buf.size() != rhs.buf.size()) return buf.size() < rhs.buf.size();
        return buf < rhs.buf;
    }

    inline void clear() {
        buf.clear();
    }

    inline int size() const {
        return buf.size();
    }

    Data& operator+= (const char ch) {
        buf.push_back(ch);
        return *this;
    }

    void printAns() {
        _for(i, 0, buf.size()) printf("%c", buf[i]);
        printf("\n");
    }

};

Data cur, ans;

bool cmp(const char a, const char b) {
    return a > b;
}

bool Less(const Data& l1, Data& l2, const Data& rhs) {
    //
    int i = 0;
    for(i = 0; i < l1.buf.size(); i++) {
        int a = l1.buf[i], b = rhs.buf[i];
        if(a < b) return true;
        if(a > b) return false;
    }

    sort(l2.buf.begin(), l2.buf.end(), cmp);
    for(; i < rhs.buf.size(); i++) {
        int a = l2.buf[i - l1.buf.size()], b = rhs.buf[i];
        if(a < b) return true;
        if(a > b) return false;
    }

    return false;
}

void bfs(int x, int y, Data& rs) {
    // get remain routes and data
    initVis();
    queue<int> que;
    que.push(x * maxc + y);
    vis[x][y] = 1;

    while(!que.empty()) {
        int t = que.front();
        que.pop();

        int nx = t / maxc, ny = t % maxc;
        _for(dir, 0, 4) {
            int nnx = nx + dx[dir], nny = ny + dy[dir];
            if(!valid(nnx, nny) || walked[nnx][nny] || vis[nnx][nny]) continue;

            vis[nnx][nny] = 1;
            rs += grid[nnx][nny];
            que.push(nnx * maxc + nny);
        }
    }
}

void dfs(int x, int y, Data& cur, Data& ans) {
    //
    Data rs;
    bfs(x, y, rs);

    if(cur.size() + rs.size() < ans.size()) return;
    if(cur.size() + rs.size() == ans.size() && Less(cur, rs, ans)) return;;

    _for(dir, 0, 4) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if(!valid(nx, ny) || walked[nx][ny]) continue;

        cur += grid[nx][ny];
        walked[nx][ny] = 1;
        dfs(nx, ny, cur, ans);
        cur.buf.pop_back();
        walked[nx][ny] = 0;
    }

    // there is no way to forward
    if(ans < cur) ans = cur;
}

int main() {
    freopen("input.txt", "r", stdin);
    while(scanf("%d%d", &R, &C) == 2 && (R || C)) {
        init();
        initVis();
        initWalk();

        _for(i, 0, R) scanf("%s", grid[i]);
        // dbg();

        ans.clear();
        _for(i, 0, R) _for(j, 0, C) {
            if(!isdigit(grid[i][j])) continue;
            cur.clear();

            // start from grid[i][j]
            cur += grid[i][j];
            walked[i][j] = 1;
            dfs(i, j, cur, ans);
            walked[i][j] = 0;
        }

        // then printf ans
        ans.printAns();
    }
}
