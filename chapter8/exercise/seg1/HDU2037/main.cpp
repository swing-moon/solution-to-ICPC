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

const int maxn = 100 + 10;

class Seg {
public:
    int l, r;
    Seg(int _l = 0, int _r = 0) : l(_l), r(_r) {}
};

Seg seg[maxn];
vector<int> chooseID;
int n;

void init() {
    chooseID.clear();
}

bool cmp(const Seg& lhs, const Seg& rhs) {
    return lhs.r < rhs.r;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &n) == 1 && n) {
        init();
        int lastR = -1;

        _for(i, 0, n) scanf("%d%d", &seg[i].l, &seg[i].r);
        sort(seg, seg + n, cmp);

        lastR = seg[0].r;
        chooseID.push_back(0);

        _for(i, 1, n) {
            if(seg[i].l >= lastR) {
                chooseID.push_back(i);
                lastR = seg[i].r;
            }
        }

        printf("%d\n", (int)chooseID.size());
    }
}