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

const int maxl = 250000 + 5;
const int maxn = maxl * 2;

llong cnt[maxn];



class SAM {
public:
    int maxlen[maxn], link[maxn], trans[maxn][26];
    int last, sz;

    SAM() {
        Set(maxlen, 0);
        Set(link, 0);
        Set(trans, 0);

        last = sz = 1;
    }

    void extend(int ch) {
        int cur = ++sz, p = last;
        maxlen[cur] = maxlen[p] + 1;
        cnt[cur] = 1;

        for( ; p && trans[p][ch] == 0; p = link[p]) trans[p][ch] = cur;

        if(p == 0) link[cur] = 1;
        else {
            int q = trans[p][ch];
            if(maxlen[q] == maxlen[p] + 1) link[cur] = q;
            else {
                int clone = ++sz;
                maxlen[clone] = maxlen[p] + 1;

                Cpy(trans[clone], trans[q]);
                link[clone] = link[q];

                for(; p && trans[p][ch] == q; p = link[p]) trans[p][ch] = clone;
                link[q] = link[cur] = clone;
            }
        }

        last = cur;
    }
};

SAM sam;

vector<int> G[maxn];
int indeg[maxn];
llong ans[maxn];

void init() {
    Set(cnt, 0);
    Set(ans, 0);
    Set(indeg, 0);
}

void build() {
    _rep(i, 1, sam.sz) {
        G[i].push_back(sam.link[i]);
        indeg[sam.link[i]]++;
    }
}

void topo() {
    queue<int> que;
    _rep(i, 0, sam.sz) if(indeg[i] == 0) que.push(i);

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        _for(i, 0, G[u].size()) {
            int v = G[u][i];
            cnt[v] += cnt[u];

            if(--indeg[v] == 0) que.push(v);
        }
    }

    _rep(i, 1, sam.sz) ans[sam.maxlen[i]] = max(ans[sam.maxlen[i]], cnt[i]);
}

// usage: build() topo()

int main() {
    freopen("input.txt", "r", stdin);
    init();

    char str[maxl];
    scanf("%s", str);
    int len = strlen(str);

    _for(i, 0, len) sam.extend(str[i] - 'a');

    build();
    topo();
    _forDown(i, len, 1) ans[i] = max(ans[i], ans[i + 1]);
    _rep(i, 1, len) cout << ans[i] << endl;
}