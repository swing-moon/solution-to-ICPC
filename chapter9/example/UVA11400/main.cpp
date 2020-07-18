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

const int maxn = 1000 + 10;
const int inf = 0x3f;
int N;

int f[maxn];

class Light {
public:
    int V;
    int K;
    int C;
    int L;

    bool operator< (const Light& rhs) const {
        return V < rhs.V;
    }
};

Light l[maxn];
int sum[maxn];

void initdp() {
    sort(l + 1, l + 1 + N);

    Set(f, inf);
    Set(sum, 0);
    f[0] = 0;

    _rep(i, 1, N) sum[i] = sum[i - 1] + l[i].L;
}

void dp() {
    _rep(i, 1, N) {
        _rep(j, 0, i - 1) f[i] = min(f[i], f[j] + (sum[i] - sum[j]) * l[i].C + l[i].K);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &N) && N) {
        _rep(i, 1, N) scanf("%d%d%d%d", &l[i].V, &l[i].K, &l[i].C, &l[i].L);

        initdp();
        dp();
        cout << f[N] << endl;
    }
}