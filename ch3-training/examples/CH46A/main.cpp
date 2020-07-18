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

const int maxn = 250000 + 5;
int n, t;

class Magnet {
public:
    int x, y, m, p, r;
};

Magnet P[maxn];
queue<Magnet> que;
int vis[maxn];
Magnet st;
int cnt = 0;

void init() {
    Set(vis, 0);
    cnt = 0;
}

bool cmp(Magnet lhs, Magnet rhs) {
    return lhs.m < rhs.m;
}

bool cmp2(Magnet a, Magnet b) {
    return (llong)(a.x - st.x) * (a.x - st.x) + (llong)(a.y - st.y) * (a.y - st.y) < (llong)(b.x - st.x) * (b.x - st.x) + (llong)(b.y - st.y) * (b.y - st.y);
}

bool attr(Magnet a, Magnet b) {
    return (llong)(b.x - st.x) * (b.x - st.x) + (llong)(b.y - st.y) * (b.y - st.y) <= (llong)a.r * a.r;
}


class Seg {
public:
    int l, r, M;
};

Seg seg[maxn];

void cal() {
    sort(P + 1, P + 1 + n, cmp);

    t = sqrt(n);
    _rep(i, 1, t) {
        seg[i].l = (i - 1) * t + 1;
        seg[i].r = i * t;
        seg[i].M = P[seg[i].r].m;

        sort(P + seg[i].l, P + seg[i].r + 1, cmp2);
    }

    if(seg[t].r < n) {
        t++;
        seg[t].l = seg[t - 1].r + 1;
        seg[t].r = n;
        seg[t].M = P[n].m;

        sort(P + seg[t].l, P + seg[t].r + 1, cmp2);
    }
}

void bfs() {
    que.push(st);
    cnt = 1;

    while (!que.empty()) {
        Magnet cur = que.front();
        que.pop();

        //cout << cur.x << " " << cur.y << endl;

        int k = 0;
        _rep(i, 1, t) {
            if(seg[i].M <= cur.p) k = i;
            else break;
        }

        _rep(i, 1, k) {
            while (seg[i].l <= seg[i].r && attr(cur, P[seg[i].l])) {
                // check attr, and push
                if(!vis[seg[i].l]) {
                    vis[seg[i].l] = 1;
                    que.push(P[seg[i].l]);
                    cnt++;
                }

                seg[i].l++;
            }
        }

        if(k != t) {
            k++;
            _rep(i, seg[k].l, seg[k].r) {
                if(!vis[i] && P[i].m <= cur.p && attr(cur, P[i])) {
                    vis[i] = 1;
                    que.push(P[i]);
                    cnt++;
                }
            }
        }
    }

    cout << cnt - 1 << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    init();
    cin >> st.x >> st.y >> st.p >> st.r >> n;
    _rep(i, 1, n) scanf("%d %d %d %d %d", &P[i].x, &P[i].y, &P[i].m, &P[i].p, &P[i].r);

    // == split into block
    cal();
    // == split into block finished

    // == bfs
    bfs();
    // == bfs finished
}