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

const int maxn = 300 + 5;
const int MOD = 1000000000;
char str[maxn];
int N;
int f[maxn][maxn];

void initdp() {
    Set(f, -1);
}

int dp(int l, int r) {
    if(l > r) return 0;
    if(l == r) return 1;
    int& ans = f[l][r];
    if(ans != -1) return ans;

    ans = 0;
    if(str[l] == str[r]) {
        for(int k = l + 2; k <= r; k++) {
            ans = (ans + (llong)dp(l + 1, k - 1) * (llong)dp(k, r)) % MOD;
        }
    }

    return ans;
}


int main() {
    freopen("input.txt", "r", stdin);
    scanf("%s", str + 1);
    N = strlen(str + 1);

    initdp();
    cout << dp(1, N) << endl;
}