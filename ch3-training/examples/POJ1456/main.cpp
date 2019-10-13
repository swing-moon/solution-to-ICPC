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

const int maxn = 10000 + 10;
int pa[maxn];
int n;

void initPa(int n) {
    _rep(i, 0, n) pa[i] = i;
}

int find(int x) {
    return x == pa[x] ? x : (pa[x] = find(pa[x]));
}

class Stuf {
public:
    int prof, day;
    bool operator< (const Stuf& rhs) const {
        return prof > rhs.prof;
    }
};

Stuf stufs[maxn];

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &n) != EOF) {

        int maxd = 0;
        _for(i, 0, n) {
            scanf("%d%d", &stufs[i].prof, &stufs[i].day);
            maxd = max(maxd, stufs[i].day);
        }

        sort(stufs, stufs + n);

        initPa(maxd);
        int ans = 0;
        _for(i, 0, n) {
            int d = find(stufs[i].day);
            if(d) {
                ans += stufs[i].prof;
                pa[d] = d - 1;
            }
        }

        printf("%d\n", ans);
    }
}