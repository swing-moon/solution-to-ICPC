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

const int maxn = 300000 + 10;
llong sumc[maxn], sumt[maxn];
llong f[maxn];

int n, s;

void init() {
    Set(f, 0x3f);
    f[0] = 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> s;
    init();

    // == get input ==
    _rep(i, 1, n) {
        int t, c;
        scanf("%d%d", &t, &c);
        sumt[i] = sumt[i - 1] + t;
        sumc[i] = sumc[i - 1] + c;
    }
    // == input finished ==

    deque<int> q;
    q.push_back(0);

    _rep(i, 1, n) {
        while (q.size() >= 2 && (f[q[1]] - f[q[0]]) <= (s + sumt[i]) * (sumc[q[1]] - sumc[q[0]]) ) q.pop_front();
        f[i] = f[q[0]] - (s + sumt[i]) * sumc[q[0]] + sumt[i] * sumc[i] + s * sumc[n];
        while (q.size() >= 2 && (f[*(q.end()-1)] - f[*(q.end()-2)]) * (sumc[i] - sumc[*(q.end()-1)]) >= (f[i] - f[*(q.end()-1)]) * (sumc[*(q.end()-1)] - sumc[*(q.end()-2)]) )
            q.pop_back();
        q.push_back(i);
    }
    cout << f[n] << endl;
}