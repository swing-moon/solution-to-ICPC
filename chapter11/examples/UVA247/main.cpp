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

const int inf = 0x3f3f3f3f;
const int maxn = 25 + 10;
const int maxl = 100;
int n, m;

// == Graph definition ==
int d[maxn][maxn], vis[maxn];
vector<string> names;

inline int ID(const string& str) {
    _for(i, 0, names.size()) {
        if(names[i] == str) return i;
    }
    names.push_back(str);
    return names.size() - 1;
}
// == Graph finished ==

// == floyd algorithm ==
void floyd() {
    _for(k, 0, n) _for(i, 0, n) _for(j, 0, n) {
        d[i][j] |= (d[i][k] & d[k][j]);
    }
}
// == floyd finsihed ==

// == dfs ==
void dfs(int u) {
    vis[u] = 1;
    _for(i, 0, n) {
        if(vis[i]) continue;
        if(d[u][i] && d[i][u]) {
            printf(", %s", names[i].c_str());
            dfs(i);
        }
    }
}
// == dfs finished ==

// == solve ==
void solve() {
    Set(vis, 0);
    _for(u, 0, n) {
        if(!vis[u]) {
            printf("%s", names[u].c_str());
            dfs(u);
            printf("\n");
        }
    }
}
// == solve finsihed ==

void init() {
    Set(d, 0);
    _for(i, 0, n) d[i][i] = 1;

    Set(vis, 0);
    names.clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    char s1[maxn], s2[maxn];
    int kase = 0;

    while (scanf("%d%d", &n, &m) == 2 && n) {
        init();

        while (m--) {
            scanf("%s%s", s1, s2);
            d[ID(s1)][ID(s2)] = 1;
        }

        floyd();

        if(kase > 0) printf("\n");
        printf("Calling circles for data set %d:\n", ++kase);

        // calculate connected components
        solve();
    }
}