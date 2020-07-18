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

const int maxn = 6000 + 5;
int H[maxn];
bool hasFa[maxn];
int f[maxn][2];
vector<int> son[maxn];
int N;

void initdp() {
    Set(f, 0);
}

void dp(int x) {
    f[x][1] = H[x];
    f[x][0] = 0;
    _for(i, 0, son[x].size()) {
        int y = son[x][i];
        dp(y);

        f[x][0] += max(f[y][0], f[y][1]);
        f[x][1] += f[y][0];
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    cin >> N;

    _rep(i, 1, N) scanf("%d", &H[i]);
    _for(i, 0, N) {
        int x, y;
        scanf("%d%d", &x, &y);
        hasFa[x] = 1;
        son[y].push_back(x);
    }

    int root = 0;
    _rep(i, 1, N) if(!hasFa[i]) {
        root = i;
        break;
    }
    assert(root != 0);

    initdp();
    // then dp
    dp(root);
    cout << max(f[root][0], f[root][1]) << endl;
}