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

const int inf = 0x3f3f3f3f;
const int maxn = 100 + 1, maxs = 160;
const int maxm = 10 + 1;
int f[maxn][maxs][maxs];
int fbid[maxn];
int cnt[maxs];
int buf[maxs];
int N, M;
int tot = 0;

void init() {
    Set(fbid, 0);
    Set(cnt, 0);
    Set(buf, 0);
    tot = 0;
}

int getone(int x) {
    int cnt = 0;
    while (x) {
        if((x & 1) == 1) cnt++;
        x >>= 1;
    }
    return cnt;
}

bool ok(int x) {
    if(x & (x << 1)) return false;
    if(x & (x << 2)) return false;
    return true;
}

inline void cal() {
    tot = 0;
    _for(st, 0, 1 << M) if(ok(st)) {
        buf[tot] = st;
        cnt[tot++] = getone(st);
    }
}

void initdp() {
    Set(f, -1);
    f[0][0][0] = 0;
}

bool valid(int i, int st) {
    if(fbid[i] & st) return false;
    return true;
}

int dp() {
    int ans = 0;
    _for(k, 0, tot) if(valid(1, buf[k])) {
        f[1][k][0] = cnt[k];
        ans = max(ans, f[1][k][0]);
        //debug(ans);
    }

    _rep(i, 2, N) {
        _for(j, 0, tot) if(valid(i, buf[j])) {
            _for(k, 0, tot) if(valid(i - 1, buf[k]) && (buf[k]&buf[j]) == 0) {
                int pre = 0;
                _for(l, 0, tot) if(f[i - 1][k][l] != -1 && valid(i - 2, buf[l]) && (buf[l]&buf[j]) == 0) {
                    pre = max(pre, f[i - 1][k][l]);
                }

                f[i][j][k] = max(f[i][j][k], pre + cnt[j]);
                if(i == N) ans = max(ans, f[i][j][k]);
            }
        }
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    init();

    scanf("%d%d", &N, &M);
    _rep(i, 1, N) {
        char t[maxm];
        scanf("%s", t);
        //debug(t);
        _for(j, 0, M) {
            if(t[j] == 'H') {
                fbid[i] |= (1 << (M-1-j));
            }
        }
        //debug(fbid[i]);
    }
    // then dp
    cal();
    initdp();
    printf("%d\n", dp());
}