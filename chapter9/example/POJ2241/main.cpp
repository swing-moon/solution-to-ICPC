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

const int maxn = 30 + 5;
int N;

int block[maxn][3];
int f[maxn][3];

void getdim(int* v, int i, int j) {
    int id = 0;
    _for(k, 0, 3) if(k != j) v[id++] = block[i][k];
}

void initdp() {
    Set(f, 0);
}

int dp(int i, int j) {
    int& ans = f[i][j];
    if(ans > 0) return ans;

    ans = 0;
    int v1[2], v2[2];
    getdim(v1, i, j);

    _for(a, 0, N) {
        //if(a == i) continue;  infinity a
        _for(b, 0, 3) {
            if(a == i && b == j) continue;
            getdim(v2, a, b);

            if(v1[0] < v2[0] && v1[1] < v2[1]) ans = max(ans, dp(a, b));
        }
    }

    ans += block[i][j];
    return ans;
}


int main() {
    freopen("input.txt", "r", stdin);
    int kase = 1;
    while (scanf("%d", &N) && N) {
        _for(i, 0, N) {
            _for(j, 0, 3) scanf("%d", &block[i][j]);
            sort(block[i], block[i] + 3);
        }

        // then dp
        initdp();
        int ret = 0;
        _for(i, 0, N) _for(j, 0, 3) ret = max(ret, dp(i, j));
        printf("Case %d: maximum height = %d\n", kase++, ret);
    }
}