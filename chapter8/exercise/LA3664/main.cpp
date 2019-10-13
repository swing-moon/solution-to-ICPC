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

const int maxn = 16384 + 5;
vector<int> per[maxn];
vector<int> rk;
int n;

void init() {
    _for(i, 0, maxn) per[i].clear();
    rk.clear();
}

int readint() {
    char buf[8];
    scanf("%s", buf);

    int a = 0, b = 0;
    sscanf(buf, "%d", &a);

    char* pp = strchr(buf, '.');
    if(pp) sscanf(++pp, "%d", &b);

    return a * 100 + b;
}

int read() {
    int x;
    scanf("%d", &x);
    return x;
}

int solve() {
    int lastScore = -1, lastID = -1;
    _for(i, 0, rk.size()) {
        int id = rk[i];
        if(lastScore == -1) lastScore = per[id].front();
        else {
            bool found = false;
            _for(j, 0, per[id].size()) {
                if(per[id][j] < lastScore || (per[id][j] == lastScore && id > lastID)) {
                    lastScore = per[id][j];
                    found = true;
                    break;
                }
            }
            if(!found) return -1;
        }
        lastID = id;
    }
    return lastScore;
}

int main() {
    freopen("input.txt", "r", stdin);
    for(int kase = 1; scanf("%d", &n) == 1 && n; kase++) {
        init();

        _for(i, 0, n) {
            per[i].clear();

            per[i].push_back(0);
            _for(j, 0, 3) per[i].push_back(readint());

            per[i].push_back(per[i][1] + per[i][2]);
            per[i].push_back(per[i][1] + per[i][3]);
            per[i].push_back(per[i][2] + per[i][3]);
            per[i].push_back(per[i][1] + per[i][2] + per[i][3]);

            sort(per[i].begin(), per[i].end(), greater<int>());
        }

        _for(i, 0, n) rk.push_back(read() - 1);

        // then solve the problem
        int ans = solve();
        if(ans == -1) printf("Case %d: No solution\n", kase);
        else printf("Case %d: %d.%02d\n", kase, ans / 100, ans % 100);
    }
}