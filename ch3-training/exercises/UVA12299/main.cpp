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

const int inf = 0x3f3f3f3f;
const int maxnode = 1<<18;
const int maxn = 100000 + 10;
int A[maxn];
int n, q;

// == struct segment tree ==
class segTree {
public:
    int l, r;
    int dat;
};
segTree tree[maxnode];
#define l(x) tree[x].l
#define r(x) tree[x].r
#define dat(x) tree[x].dat
// == struct finished ==

void build(int p, int l, int r) {
    l(p) = l, r(p) = r;
    //debug(p), debug(l(p)),debug(r(p));
    //cout << endl;
    if(l == r) {
        dat(p) = A[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    dat(p) = min(dat(p << 1), dat(p << 1 | 1));
}

void change(int p, int x, int v) {
    // change A[x] = v, segment API is change(1, x, v)
    if(l(p) == r(p)) {
        dat(p) = v;
        return;
    }

    int mid = (l(p) + r(p)) >> 1;
    if(x <= mid) change(p << 1, x, v);
    else change(p << 1 | 1, x, v);
    dat(p) = min(dat(p << 1), dat(p << 1 | 1));
}

int ask(int p, int ql, int qr) {
    if(ql <= l(p) && r(p) <= qr) return dat(p);

    int mid = (l(p) + r(p)) >> 1;
    //debug(p);
    //debug(l(p)), debug(r(p));
    int val = inf;
    if(ql <= mid) val = min(val, ask(p << 1, ql, qr));
    if(qr > mid) val = min(val, ask(p << 1 | 1, ql, qr));
    return val;
}


const int maxl = 30 + 2;
void solve(const char* cmd) {
    int args[maxl], buf[maxl];
    int len = strlen(cmd);

    int k = 0;
    args[k] = 0;
    _for(i, 6, len) {
        if(isdigit(cmd[i])) args[k] = args[k] * 10 + cmd[i] - '0';
        else {
            k++;
            args[k] = 0;
        }
    }

    // debug args

    if(cmd[0] == 'q') {
        int ql = args[0];
        int qr = args[1];
        //debug(ql);
        //debug(qr);
        //cout << endl;
        printf("%d\n", ask(1, ql, qr));
    }
    else {
        // shift rmq
        _for(i, 0, k) buf[i] = A[args[i]];
        _for(i, 0, k) {
            int p = args[i];
            A[p] = buf[(i + 1) % k];
            int v = A[p];
            change(1, p, v);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    cin >> n >> q;
    _rep(i, 1, n) scanf("%d", &A[i]);
    build(1, 1, n);

    while (q--) {
        char cmd[maxl];
        scanf("%s", cmd);
        //debug(cmd);
        solve(cmd);
    }
}