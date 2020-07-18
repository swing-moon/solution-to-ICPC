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

const int maxn = 100000 + 10;
const int inf = 0x3f3f3f3f;

class Treap {
public:
    int l, r;
    int val, rk;
    int cnt, sz;
};

Treap a[maxn];
int tot, root, n;

void init() {
    tot = 0;
}

int New(int val) {
    a[++tot].val = val;
    a[tot].rk = rand();
    a[tot].cnt = a[tot].sz = 1;
    return tot;
}

void Update(int p) {
    a[p].sz = a[a[p].l].sz + a[a[p].r].sz + a[p].cnt;
}

void build() {
    New(-inf), New(inf);
    root = 1, a[1].r = 2;
    Update(root);
}

int rankByVal(int p, int val) {
    if(p == 0) return 0;
    if(val == a[p].val) return a[a[p].l].sz + 1;
    if(val < a[p].val) return rankByVal(a[p].l, val);
    return a[a[p].l].sz + a[p].cnt + rankByVal(a[p].r, val);
}

int valByRank(int p, int rank) {
    if(p == 0) return inf;
    if(a[a[p].l].sz >= rank) return valByRank(a[p].l, rank);
    if(a[a[p].l].sz + a[p].cnt >= rank) return a[p].val;
    return valByRank(a[p].r, rank - a[a[p].l].sz - a[p].cnt);
}

void zig(int& p) {
    int q = a[p].l;
    a[p].l = a[q].r, a[q].r = p, p = q;
    Update(a[p].r), Update(p);
}

void zag(int& p) {
    int q = a[p].r;
    a[p].r = a[q].l, a[q].l = p, p = q;
    Update(a[p].l), Update(p);
}

void insert(int& p, int val) {
    if(p == 0) {
        p = New(val);
        return;
    }
    if(val == a[p].val) {
        a[p].cnt++;
        Update(p);
        return;;
    }

    if(val < a[p].val) {
        insert(a[p].l, val);
        if(a[p].rk < a[a[p].l].rk) zig(p);
    }
    else {
        insert(a[p].r, val);
        if(a[p].rk < a[a[p].r].rk) zag(p);
    }
    Update(p);
}

void remove(int& p, int val) {
    if(p == 0) return;
    if(val == a[p].val) {
        if(a[p].cnt > 1) {
            a[p].cnt--;
            Update(p);
            return;
        }

        if(a[p].l && a[p].r) {
            if(a[a[p].l].rk > a[a[p].r].rk) {
                zig(p);
                remove(a[p].r, val);
            }
            else {
                zag(p);
                remove(a[p].l, val);
            }
        }
        else {
            if(a[p].l == 0 && a[p].r == 0) {
                p = 0;
                return;
            }
            else if(a[p].r == 0) p = a[p].l;
            else p = a[p].r;
        }
    }
    else {
        val < a[p].val ? remove(a[p].l, val) : remove(a[p].r, val);
    }
    if(p != 0) Update(p);
}

int getPre(int val) {
    int ans = 1;
    int p = root;

    while (p) {
        if(val == a[p].val) {
            if(a[p].l > 0) {
                p = a[p].l;
                while (a[p].r > 0) p = a[p].r;
                ans = p;
            }
            break;
        }
        if(a[p].val < val && a[p].val > a[ans].val) ans = p;
        p = val < a[p].val ? a[p].l : a[p].r;
    }
    return a[ans].val;
}

int getNext(int val) {
    int ans = 2;
    int p = root;

    while (p) {
        if(val == a[p].val) {
            if(a[p].r > 0) {
                p = a[p].r;
                while (a[p].l > 0) p = a[p].l;
                ans = p;
            }
            break;
        }

        if(a[p].val > val && a[p].val < a[ans].val) ans = p;
        p = val < a[p].val ? a[p].l : a[p].r;
    }

    return a[ans].val;
}

int main() {
    freopen("input.txt", "r", stdin);
    init();
    cin >> n;
    build();
    while (n--) {
        int op, x;
        scanf("%d%d", &op, &x);

        switch (op){
            case 1:
                insert(root, x);
                break;
            case 2:
                remove(root, x);
                break;
            case 3:
                printf("%d\n", rankByVal(root, x) - 1);
                break;
            case 4:
                printf("%d\n", valByRank(root, x + 1));
                break;
            case 5:
                printf("%d\n", getPre(x));
                break;
            case 6:
                printf("%d\n", getNext(x));
                break;
        }
    }
}