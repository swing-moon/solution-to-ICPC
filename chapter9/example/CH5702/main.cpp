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

const int maxl = 100 + 5, maxn = 1000000 + 5;
const int maxlog = 30;

llong f[maxl][maxlog + 2];
string s1, s2;
int n1, n2;

void init() {
    Set(f, 0);
}

inline bool cal() {
    _for(i, 0, s1.size()) {
        int p = i;
        f[i][0] = 0;
        _for(j, 0, s2.size()) {
            int cnt = 0;

            // then try to find s1[p] matched s2[j]
            while (s1[p] != s2[j]) {
                p = (p + 1) % (int)s1.size();
                if(++cnt >= s1.size()) {
                    cout << 0 << endl;
                    return false;
                }
            }

            p = (p + 1) % (int)s1.size();
            f[i][0] += cnt + 1;
        }
    }
    return true;
}

void dp() {
    _rep(j, 1, maxlog) _for(i, 0, s1.size()) {
        f[i][j] = f[i][j - 1] + f[(i + f[i][j-1] ) % s1.size()][j - 1];
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    while (cin >> s2 >> n2 >> s1 >> n1) {
        init();
        // debug(s2);
        if(!cal()) continue;

        dp();

        llong m = 0;
        _for(st, 0, s1.size()) {
            llong x = st, ans = 0;

            // then connect 2^k
            _forDown(k, maxlog, 0) {
                if(x + f[x % s1.size()][k] <= n1 * s1.size()) {
                    x += f[x % s1.size()][k];
                    ans += (1 << k);
                }
            }

            m = max(m, ans);
        }

        cout << m / n2 << endl;
    }
}