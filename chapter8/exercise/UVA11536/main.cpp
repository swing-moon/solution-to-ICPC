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

const int maxn = 1000000 + 10;
int n, m, k;
int x[maxn];

void cal() {
    _for(i, 0, n) {
        if(i < 3) x[i] = i + 1;
        else x[i] = (x[i - 3] + x[i - 2] + x[i - 1]) % m + 1;
    }
}

bool valid(int x) {
    return 1 <= x && x <= k;
}

void ins(int x, map<int, int>& win) {
    if(valid(x)) win[x] = win[x] + 1;
}

void del(int x, map<int, int>& win) {
    if(!win.count(x)) return;
    win[x] = win[x] - 1;
    if(win[x] < 1) win.erase(x);
}

int solve() {
    map<int, int> win;
    win.clear();

    int ans = 0;

    for(int L = 0, R = 0; L < n && R < n; L++) {
        while (win.size() < k) {
            ins(x[R], win);
            R++;
            if(R >= n) break;
        }


        if(win.size() == k) {
            // enough points

            while (win[x[L]] > 1 || !win.count(x[L])) {
                del(x[L], win);
                L++;
            }

            if(!ans) ans = R - L + 1;
            else ans = min(ans, R - L + 1);
        }

        del(x[L], win);
    }

    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    _rep(t, 1, T) {
        scanf("%d%d%d", &n, &m, &k);

        // then we init cal() x[] and solve()

        cal();

        printf("Case %d: ", t);

        int ans = solve();
        if(!ans) printf("sequence nai\n");
        else printf("%d\n", ans - 1);
    }
}