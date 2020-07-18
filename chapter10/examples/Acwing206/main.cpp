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

const int maxn = 10 + 5;
const int inf = 0x3f3f3f3f;
int n, m, t, act, N;

// == board definition ==
char str[maxn], op[maxn][maxn];
int bd[maxn][maxn], ptr[maxn][maxn];
// == board definition finished ==

// == get hash ==
inline int _hash(int i, int j) {
    return (i - 1) * m + j;
}

vector<vector<ll> > A[60 + 5];
vector<vector<ll> > F;

void initHash() {
    N = n * m + 1;
    _rep(i, 1, 60) A[i].resize(N, vector<ll>(N));
    F.resize(1, vector<ll>(N));
    F[0][0] = 1;
    _rep(i, 1, 60) A[i][0][0] = 1;
}
// == hash finished ==

// == build matrix ==
void build() {
    _rep(k, 1, 60) {
        _rep(i, 1, n) _rep(j, 1, m) {
            int x = bd[i][j], y = ptr[i][j];

            if(isdigit(op[x][y])) {
                A[k][0][_hash(i, j)] = op[x][y] - '0';
                A[k][_hash(i, j)][_hash(i, j)] = 1;
            }
            else if(op[x][y] == 'N' && i > 1) A[k][_hash(i, j)][_hash(i-1, j)] = 1;
            else if(op[x][y] == 'S' && i < n) A[k][_hash(i, j)][_hash(i+1, j)] = 1;
            else if(op[x][y] == 'W' && j > 1) A[k][_hash(i, j)][_hash(i, j-1)] = 1;
            else if(op[x][y] == 'E' && j < m) A[k][_hash(i, j)][_hash(i, j+1)] = 1;

            ptr[i][j] = (ptr[i][j] + 1) % strlen(op[x]);
        }
    }
}
// == build matrix finished ==

// == calculate ==
inline void mul(vector<vector<ll> > &A, const vector<vector<ll> > &B) {
    vector<vector<ll> > ans;
    ans.resize(A.size(), vector<ll>(B[0].size()));

    _for(i, 0, A.size()) _for(j, 0, B[0].size()) {
        _for(k, 0, B.size()) ans[i][j] = ans[i][j] + A[i][k] * B[k][j];
    }

    A = ans;
}

void solve() {
    vector<vector<ll> > C = A[1];
    _rep(i, 2, 60) mul(C, A[i]);

    ll ans = 0;
    int q = t / 60;
    for(; q; q >>= 1) {
        if(q & 1) mul(F, C);
        mul(C, C);
    }

    int r = t % 60;
    _rep(i, 1, r) mul(F, A[i]);

    _for(i, 0, N) ans = max(ans, F[0][i]);
    cout << ans << endl;
}
// == calculate finsihed ==

void init() {
    Set(ptr, 0);
}

int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> m >> t >> act;

    init();
    // get input board
    _rep(i, 1, n) {
        scanf("%s", str + 1);
        _rep(j, 1, m) bd[i][j] = str[j] - '0';
    }
    // get command
    _for(i, 0, act) scanf("%s", op[i]);

    // == input finished ==

    // init Hash and build matrix
    initHash();
    build();

    // calculate
    solve();
}