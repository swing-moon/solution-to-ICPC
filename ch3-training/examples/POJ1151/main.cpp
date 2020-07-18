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

const int maxn = 100 + 5;
int N, m;
int kase = 0;

class Node {
public:
    double x, y1, y2;
    int k;
    bool operator< (const Node& rhs) const {
        return x < rhs.x;
    }
};

Node A[maxn << 1];
map<double, int> ny;
double raw[maxn << 1];

void init() {
    Set(raw, 0);
    ny.clear();
}

void dicrete() {
    sort(raw + 1, raw + 1 + N);
    m = unique(raw + 1, raw + 1 + N) - (raw + 1);
    _rep(i, 1, m) ny[raw[i]] = i;
}

class Tree {
public:
    int l, r, cnt;
    double len;
#define l(x) tree[x].l
#define r(x) tree[x].r
#define cnt(x) tree[x].cnt
#define len(x) tree[x].len
} tree[maxn << 3];

void build(int p, int l, int r) {
    l(p) = l; r(p) = r; len(p) = 0; cnt(p) = 0;
    if(l == r) return;

    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

void change(int p, int l, int r, int d) {
    if(l <= l(p) && r(p) <= r) len(p) = ((cnt(p) += d) ? raw[r(p)+1] - raw[l(p)] : 0);
    if(l(p) == r(p)) return;

    int mid = (l(p) + r(p)) >> 1;
    if(l <= mid) change(p << 1, l, r, d);
    if(r > mid) change(p << 1 | 1, l, r, d);

    len(p) = (cnt(p) ? raw[r(p)+1] - raw[l(p)] : len(p<<1) + len(p<<1 | 1));
}

double atlantis() {
    sort(A + 1, A + 1 + N);
    build(1, 1, m - 1);
    // use subscribe to build seg tree

    double ans = 0;
    // scan line
    _for(i, 1, N) {
        int y1 = ny[A[i].y1], y2 = ny[A[i].y2] - 1;
        change(1, y1, y2, A[i].k);
        ans += len(1) * (A[i + 1].x - A[i].x);
    }
    printf("Test case #%d\nTotal explored area: %.2f\n\n", ++kase, ans);
}

int main() {
    freopen("input.txt", "r", stdin);
    while (cin >> N && N) {
        init();

        _rep(i, 1, N) {
            int k = i << 1;
            double y1, y2;
            scanf("%lf %lf %lf %lf", &A[k-1].x, &y1, &A[k].x, &y2);
            raw[k-1] = A[k-1].y1 = A[k].y1 = y1;
            raw[k] = A[k-1].y2 = A[k].y2 = y2;
            A[k-1].k = 1;
            A[k].k = -1;
        }
        N <<= 1;

        // discrete()
        // oldY --ny()--> newY, raw[1-m]--> oldY
        dicrete();
        atlantis();
    }
}