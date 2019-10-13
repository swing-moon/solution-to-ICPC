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

const int maxn = 100000 + 10;
int A[maxn * 3], cnt[maxn], ok[maxn * 2];
int n, s;

void init() {
    Set(A, -1);
    Set(cnt, 0);
    Set(ok, 0);
}

void slideWin() {
    int tot = 0;
    _for(i, 0, s + n + 1) {
        // i is start of slide win
        if(tot == s) ok[i] = 1;
        if(i < s && tot == i) ok[i] = 1;
        if(i > n && tot == n + s - i) ok[i] = 1;

        if(i == s + n) break;

        // then slide to next position
        if(A[i] != -1 && --cnt[A[i]] == 0) tot--;
        if(A[i + s] != -1 && cnt[A[i + s]]++ == 0) tot++;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    cin >> T;
    while (T--) {
        init();
        cin >> s >> n;
        _for(i, 0, n) cin >> A[s + i];

        slideWin();

        int ans = 0;
        _for(i, 0, s) {
            int valid = 1;
            for(int j = i; j < s + n + 1; j += s) if(!ok[j]) valid = 0;
            if(valid) ans++;
        }
        if(ans >= n + 1) ans = s;
        cout << ans << "\n";
    }
}