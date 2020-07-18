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

const int maxn = 200 + 10;
const int inf = 0x3f3f3f3f;
int n, t, s, e, tot = 0;

map<int, int> mp;

// == status definition ==
struct Mat {
    int A[maxn][maxn];

    void _init() {
        _for(i, 1, maxn) _for(j, 1, maxn) {
                A[i][j] = inf;
            }
    }
} st, ed;
// == status finished ==

inline Mat mul(Mat a, Mat b) {
    Mat c;
    c._init();
    _rep(i, 1, tot) _rep(j, 1, tot) _rep(k, 1, tot) {
                c.A[i][j] = min(c.A[i][j], a.A[i][k] + b.A[k][j]);
            }
    return c;
}

void init() {
    tot = 0;
    mp.clear();
    st._init();
    ed._init();
}

int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> t >> s >> e;
    init();

    // build Graph
    while (t--) {
        int x, y, z;
        scanf("%d%d%d", &z, &x, &y);
        x = mp[x] ? mp[x] : (mp[x] = ++tot);
        y = mp[y] ? mp[y] : (mp[y] = ++tot);
        st.A[x][y] = st.A[y][x] = z;
    }
    Cpy(ed.A, st.A);

    // Matrix change
    n--;
    for(; n; n >>= 1) {
        if(n & 1) ed = mul(ed, st);
        st = mul(st, st);
    }

    cout << ed.A[mp[s]][mp[e]] << endl;
}