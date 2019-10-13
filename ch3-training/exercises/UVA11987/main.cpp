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
int n, m;
int pa[maxn], cnt[maxn], id[maxn];
llong sum[maxn];
int tot;

void init(int n) {
    _rep(i, 0, n) {
        pa[i] = i;
        id[i] = i;
        sum[i] = i;
        cnt[i] = 1;
    }
    tot = n;
}

int find(int x) {
    return x == pa[x] ? x : (pa[x] = find(pa[x]));
}

void Union(int p, int q) {
    int rootp = find(p);
    int rootq = find(q);

    pa[rootp] = rootq;
    sum[rootq] += sum[rootp];
    cnt[rootq] += cnt[rootp];
}

void change(int p) {
    int pre = find(id[p]);
    sum[pre] -= p;
    cnt[pre]--;

    id[p] = ++tot;
    pa[id[p]] = id[p];
    sum[id[p]] = (llong)p;
    cnt[id[p]] = 1;
}


int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) != EOF) {
        init(n);
        _for(i, 0, m) {
            //
            int op;
            scanf("%d", &op);

            if(op == 1) {
                //
                int p, q;
                scanf("%d%d", &p, &q);
                if(find(id[p]) != find(id[q])) {
                    Union(id[p], id[q]);
                }
            }

            if(op == 2) {
                //
                int p, q;
                scanf("%d%d", &p, &q);
                if(find(id[p]) == find(id[q])) continue;

                change(p);
                Union(id[p], id[q]);
            }

            if(op == 3) {
                // print ans
                int p;
                scanf("%d", &p);
                int root = find(id[p]);
                printf("%d %lld\n", cnt[root], sum[root]);
            }

        }


    }
}