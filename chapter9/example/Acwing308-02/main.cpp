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


// == Big Integer class ==
const int SZ = 200 + 5;

inline void write(ll x) {
    if(x < 0) {
        putchar('-');
        x = -x;
    }
    if(x < 10) {
        putchar(x + '0');
        return;
    }

    write(x / 10);
    putchar((x % 10) + '0');
}

const int base = 1e4;
class Int {
public:
    int a[SZ], len;
    Int() {
        Set(a, 0);
        len = 0;
    }
    Int(int x) {
        Set(a, 0);
        len = 0;

        while (x) {
            a[++len] = x % base;
            x /= base;
        }
    }
    inline void print() {
        write(a[len]);
        for(int i = len - 1; i; i--) {
            if(a[i] < 1000) putchar('0');
            if(a[i] < 100) putchar('0');
            if(a[i] < 10) putchar('0');
            write(a[i]);
        }
    }
};

inline Int operator+ (Int a, Int b) {
    Int ans;
    ans = a;

    ans.len = max(a.len, b.len);
    _rep(i, 1, ans.len) {
        ans.a[i] += b.a[i];
        ans.a[i + 1] += ans.a[i] / base;
        ans.a[i] %= base;
    }
    while (ans.a[ans.len + 1]) ans.len++;
    return ans;
}

inline Int operator / (Int a, int b) {
    Int ans;
    assert(ans.len == 0);

    int num = 0;
    for(int i = a.len; i; i--) {
        num = num * base + a.a[i];
        ans.a[i] = num / b;
        num %= b;

        if(ans.len == 0 && ans.a[i]) ans.len = i;
    }
    return ans;
}

inline ll operator % (Int a, int b) {
    ll num = 0;
    for(int i = a.len; i; i--) {
        num = ((num * base) % b + a.a[i]) % b;
    }
    return num;
}

inline Int operator* (Int a, int b) {
    Int ans = a;
    _rep(i, 1, ans.len) ans.a[i] *= b;
    _rep(i, 1, ans.len) {
        ans.a[i + 1] += ans.a[i] / base;
        ans.a[i] %= base;
    }

    while (ans.a[ans.len + 1]) {
        ans.len++;
        ans.a[ans.len + 1] += ans.a[ans.len] / base;
        ans.a[ans.len] %= base;
    }
    return ans;
}

inline Int operator* (Int a, Int b) {
    Int ans;
    assert(ans.a[1] == 0);

    ans.len = a.len + b.len;
    _rep(i, 1, a.len) _rep(j, 1, b.len) {
            ans.a[i+j-1] += a.a[i] * b.a[j];
            ans.a[i+j] += ans.a[i+j-1] / base;
            ans.a[i+j-1] %= base;
        }
    while (ans.a[ans.len] == 0) ans.len--;
    return ans;
}

inline Int operator- (Int a, Int b) {
    Int ans = a;
    _rep(i, 1, b.len) {
        ans.a[i] -= b.a[i];
        if(ans.a[i] < 0) {
            ans.a[i + 1]--;
            ans.a[i] += base;
        }
    }

    while (ans.a[ans.len] == 0) ans.len--;
    return ans;
}

// == Big Integer class finished ==

// == init ==
const int Max = 1500;
Int bin[Max * 2];

void initbin() {
    bin[0] = Int(1);
    _rep(i, 1, Max) bin[i] = bin[i - 1] * 2;
}

const int maxn = 52;
Int c[maxn + 5][maxn + 5];

void initc() {
    c[0][0] = Int(1);
    _rep(i, 1, maxn) {
        c[i][0] = Int(1);
        _rep(j, 1, i) c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    }
}
// == init finished ==

// == initbin() initc(), then dp() ==
Int Ans[maxn + 5];

void dp() {
    Ans[1] = Int(1);
    _rep(i, 2, maxn) {
        Ans[i] = bin[i*(i-1) / 2];
        _for(j, 1, i) {
            Ans[i] = Ans[i] - (Ans[j] * c[i-1][j-1] * bin[(i-j)*(i-j-1) / 2]);
        }
    }
}
// == dp finished ==

const int mod = 1e9 + 7;


// == first get table and list H[] ==
ll H[maxn];

void initH() {
    Set(H, 0);
    H[1] = 1;
}

void table() {
    initH();
    _rep(i, 1, maxn) {
        H[i] = Ans[i] % mod;
    }
}
// == table finished ==

// ====================================================================


int main() {
    //freopen("input.txt", "r", stdin);
    freopen("ans.out", "w", stdout);

    initbin();
    initc();
    dp();

    //int n;
    // while (cin >> n && n) f[n].print(), puts("");


    /*
    _rep(i, 1, 50) {
        ll res = f[i] % mod;
        printf("%lld\n", res);
    }
    */

    // == table H[] and list ==
    table();
    _rep(i, 1, maxn) printf("%lld,\n", H[i]);
    // == table finsihed ==

    cout << "\n==================\n" << endl;
}