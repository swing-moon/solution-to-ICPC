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
int A[maxn * 3], ok[maxn * 3];
map<int, int> win;
typedef map<int, int>::iterator mii;

int n, s;

void init() {
    Set(A, -1);
    Set(ok, 0);
    win.clear();
}

// i is the index of A[i]
bool ins(int i, map<int, int>& win) {
    int first = 0;
    if(!win.count(A[i])) first = true;
    win[A[i]] = win[A[i]] + 1;

    return first;
}

bool del(int i, map<int, int>& win) {
    if(!win.count(A[i])) return false;

    win[A[i]] = win[A[i]] - 1;
    if(win[A[i]] < 1) {
        win.erase(A[i]);
        return true;
    }
    else return false;
}



void slide() {
    win.clear();
    int cnt = 0;

    _for(i, 0, s + n + 1) {
        if(cnt == s) ok[i] = true;
        if(i < s && cnt == i) ok[i] = true;
        if(i + s > s + n && cnt == s + n - i) ok[i] = true;

        if(i == s + n) break;

        if(A[i] != -1 && del(i, win)) cnt--;
        if(A[i + s] != -1 && ins(i + s, win)) cnt++;
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

        // then solve the problem
        slide();

        int ans = 0;
        _for(i, 0, s) {
            bool valid = 1;
            for(int j = i + 1; j < s + n + 1; j += s) if(!ok[j]) valid = false;

            if(valid) ans++;
        }

        if(ans >= n + 1) ans = s;
        printf("%d\n", ans);
    }
}