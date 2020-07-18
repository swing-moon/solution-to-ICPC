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

// == enumerate permutation ==
/*
int LEFT[] = {4, 0, 2, 3, 5, 1};
int UP[] = {2, 1, 5, 0, 4, 3};

void rot(int *trans, int *A) {
    int q[6];
    memcpy(q, A, sizeof(q));
    _for(i, 0, 6) A[i] = trans[q[i]];
}

void enumerate() {
    int E[6] = {0, 1, 2, 3, 4, 5};

    _for(i, 0, 6) {
        int A[6];
        memcpy(A, E, sizeof(E));
        if(i == 0) rot(UP, A);
        if(i == 1) {
            rot(LEFT, A);
            rot(UP, A);
        }
        if(i == 3) {
            rot(UP, A);
            rot(UP, A);
        }
        if(i == 4) {
            rot(LEFT, A);
            rot(LEFT, A);
            rot(LEFT, A);
            rot(UP, A);
        }
        if(i == 5) {
            rot(LEFT, A);
            rot(LEFT, A);
            rot(UP, A);
        }

        _for(k, 0, 4) {
            printf("{%d, %d, %d, %d, %d, %d},\n", A[0], A[1], A[2], A[3], A[4], A[5]);
            rot(LEFT, A);
        }
    }
}
// == enumerate finsihed ==

int main() {
    freopen("out.txt", "w", stdout);
    enumerate();
}
*/

/*
{2, 1, 5, 0, 4, 3},
{2, 0, 1, 4, 5, 3},
{2, 4, 0, 5, 1, 3},
{2, 5, 4, 1, 0, 3},
{4, 2, 5, 0, 3, 1},
{5, 2, 1, 4, 3, 0},
{1, 2, 0, 5, 3, 4},
{0, 2, 4, 1, 3, 5},
{0, 1, 2, 3, 4, 5},
{4, 0, 2, 3, 5, 1},
{5, 4, 2, 3, 1, 0},
{1, 5, 2, 3, 0, 4},
{5, 1, 3, 2, 4, 0},
{1, 0, 3, 2, 5, 4},
{0, 4, 3, 2, 1, 5},
{4, 5, 3, 2, 0, 1},
{1, 3, 5, 0, 2, 4},
{0, 3, 1, 4, 2, 5},
{4, 3, 0, 5, 2, 1},
{5, 3, 4, 1, 2, 0},
{3, 4, 5, 0, 1, 2},
{3, 5, 1, 4, 0, 2},
{3, 1, 0, 5, 4, 2},
{3, 0, 4, 1, 5, 2},
*/


const int D[24][6] = {
        {2, 1, 5, 0, 4, 3},
        {2, 0, 1, 4, 5, 3},
        {2, 4, 0, 5, 1, 3},
        {2, 5, 4, 1, 0, 3},
        {4, 2, 5, 0, 3, 1},
        {5, 2, 1, 4, 3, 0},
        {1, 2, 0, 5, 3, 4},
        {0, 2, 4, 1, 3, 5},
        {0, 1, 2, 3, 4, 5},
        {4, 0, 2, 3, 5, 1},
        {5, 4, 2, 3, 1, 0},
        {1, 5, 2, 3, 0, 4},
        {5, 1, 3, 2, 4, 0},
        {1, 0, 3, 2, 5, 4},
        {0, 4, 3, 2, 1, 5},
        {4, 5, 3, 2, 0, 1},
        {1, 3, 5, 0, 2, 4},
        {0, 3, 1, 4, 2, 5},
        {4, 3, 0, 5, 2, 1},
        {5, 3, 4, 1, 2, 0},
        {3, 4, 5, 0, 1, 2},
        {3, 5, 1, 4, 0, 2},
        {3, 1, 0, 5, 4, 2},
        {3, 0, 4, 1, 5, 2}
};

// D[r[i]] get posture of ith cube

int n;
const int maxn = 4;
int ori[maxn][6];
int cube[maxn][6];
int r[maxn];
int ans;
vector<string> data;

void init() {
    ans = n * 6;
    data.clear();
    Set(r, 0);
}

inline int getID(const char *name) {
    string str(name);
    _for(i, 0, data.size()) {
        if(data[i] == str) return i;
    }
    data.push_back(str);
    return data.size() - 1;
}

// == check ==
void inv(int ori[][6], const int cube[][6]) {
    _for(i, 0, n) _for(j, 0, 6) {
        int p = D[r[i]][j];
        ori[i][p] = cube[i][j];
    }
}

void check() {
    inv(ori, cube);

    int tot = 0;
    _for(k, 0, 6) {
        int Max = 0;
        int cnt[maxn * 6];
        Set(cnt, 0);
        _for(i, 0, n) Max = max(Max, ++cnt[ori[i][k]]);
        tot += n - Max;
    }
    ans = min(ans, tot);
}
// == check finished ==

// == dfs ==
void dfs(int d) {
    if(d == n) check();
    else {
        _for(i, 0, 24) {
            r[d] = i;
            dfs(d + 1);
        }
    }
}
// == dfs finished ==

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &n) == 1 && n) {
        init();

        // get data of cubes
        _for(i, 0, n) _for(j, 0, 6) {
            char name[30];
            scanf("%s", name);
            cube[i][j] = getID(name);
        }

        dfs(1);

        printf("%d\n", ans);
    }
}
