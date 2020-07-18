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

const int maxn = 200 + 5;
const int inf = 0x3f3f3f3f;
map<string, int> dic;
int tot = 0;
int N, M;

vector<int> son[maxn];
bool hasFa[maxn];
int cost[maxn];
int sum[maxn];
int f[maxn][maxn];

void init() {
    dic.clear();
    tot = 0;
    Set(hasFa, 0);
    Set(sum, 0);
    _for(i, 0, maxn) son[i].clear();
}

void initdp() {
    _rep(i, 1, N) if(!hasFa[i]) son[0].push_back(i);
    Set(f, inf);
    f[0][0] = 0;
}

void dp(int u) {
    f[u][0] = 0;
    sum[u] = 1;

    _for(i, 0, son[u].size()) {
        int v = son[u][i];
        dp(v);

        sum[u] += sum[v];
        //debug(sum[u]);
        _forDown(t, N, 1) _forDown(j, t, 0) {
            if(t - j < 0) continue;
            f[u][t] = min(f[u][t], f[v][j] + f[u][t - j]);
        }
    }
    if(u) f[u][sum[u]] = cost[u];
}

int main() {
    freopen("input.txt", "r", stdin);
    string data;
    while (getline(cin, data)) {
        if(data[0] == '#') break;
        init();
        stringstream ss(data);
        ss >> N >> M;
        //debug(N), debug(M);
        _for(i, 0, N) {
            getline(cin, data);
            stringstream ss(data);
            string ctry, dctry;
            int x;

            ss >> ctry >> x;
            //debug(ctry), debug(x);
            if(!dic.count(ctry)) dic[ctry] = ++tot;
            cost[dic[ctry]] = x;
            //debug(dic[ctry]);

            while (ss >> dctry) {
                //debug(dctry);
                if(!dic.count(dctry)) dic[dctry] = ++tot;
                //debug(dic[dctry]);
                son[dic[ctry]].push_back(dic[dctry]);
                hasFa[dic[dctry]] = 1;
            }
        }
        //puts("");
        // input finished
        assert(tot == N);
        initdp();
        //for(auto x : son[0]) cout << x << " ";
        dp(0);

        int ans = inf;
        _forDown(k, N, M) ans = min(ans, f[0][k]);
        printf("%d\n", ans);
    }
}