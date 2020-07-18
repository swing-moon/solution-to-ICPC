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

const int maxn = 16000 + 10;
const int maxm = 100 + 10;

class Node {
public:
    int S, L, P;

    bool operator< (const Node& rhs) const {
        return S < rhs.S;
    }
};

Node A[maxn];
int n, m;

int f[maxm][maxn];

void init() {
    Set(f, 0);
}

inline int g(int i, int k) {
    return f[i - 1][k] - A[i].P * k;
}

void solve() {
    sort(A + 1, A + 1 + m);

    deque<int> que;
    _rep(i, 1, m) {
        // == init queue ==
        for(int k = max(0, A[i].S - A[i].L); k <= A[i].S - 1; k++) {
            while (!que.empty() && g(i, que.back()) <= g(i, k)) que.pop_back();
            que.push_back(k);
        }
        // == init finished ==

        _rep(j, 1, n) {
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            if(j >= A[i].S) {
                while (!que.empty() && j - A[i].L > que.front()) que.pop_front();

                if(!que.empty()) f[i][j] = max(f[i][j], A[i].P * j + g(i, que.front()));
            }
        }
    }

    cout << f[m][n] << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> m;

    // == input ==
    _rep(i, 1, m) {
        scanf("%d%d%d", &A[i].L, &A[i].P, &A[i].S);
    }
    // == input finished ==

    init();

    solve();
}