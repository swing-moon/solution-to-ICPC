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

const int maxn = 20 + 5;
const int N = 20;
int n;
ll m, f[maxn][maxn][2];

void prework() {
    Set(f, 0);
    f[1][1][1] = f[1][1][0] = 1;

    _rep(i, 2, N) _rep(j, 1, i) {
        _rep(p, j, i - 1) f[i][j][0] += f[i - 1][p][1];
        _rep(p, 1, j - 1) f[i][j][1] += f[i - 1][p][0];
    }
}


bool used[maxn];

void solve() {
    Set(used, 0);

    int last, k;
    _rep(j, 1, n) {
        if(f[n][j][1] >= m) {
            last = j;
            k = 1;
            break;
        }
        else m -= f[n][j][1];

        if(f[n][j][0] >= m) {
            last = j;
            k = 0;
            break;
        }
        else m -= f[n][j][0];
    }

    //debug(last);
    //debug(k);

    used[last] = 1;
    printf("%d", last);

    _rep(i, 2, n) {
        int j = 0;
        k ^= 1;

        // assign new len to last
        // find out a new len, then get last len
        _rep(len, 1, n) {
            if(used[len]) continue;
            j++;

            if((k == 0 && len < last) || (k == 1 && len > last)) {
                // assign a new value to last
                if(f[n - i + 1][j][k] >= m) {
                    last = len;
                    break;
                }
                else m -= f[n - i + 1][j][k];
            }
        }

        used[last] = 1;
        printf(" %d", last);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    prework();

    int kase;
    cin >> kase;
    while (kase--) {
        cin >> n >> m;
        solve();
        cout << endl;
    }
}