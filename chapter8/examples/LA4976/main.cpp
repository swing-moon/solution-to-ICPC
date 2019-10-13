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

const int maxn = 200000 + 10;
int n, a[maxn], f[maxn], g[maxn];

void init() {
    Set(a, 0);
    Set(f, 0);
    Set(g, 0);
}

void initCal() {
    g[0] = 1;
    _for(i, 1, n) {
        if(a[i] > a[i - 1]) g[i] = g[i - 1] + 1;
        else g[i] = 1;
    }

    f[n - 1] = 1;
    _forDown(i, n - 2, 0) {
        if(a[i] < a[i + 1]) f[i] = f[i + 1] + 1;
        else f[i] = 1;
    }
}

class Node {
public:
    int A, g;
    Node(int _A = 0, int _g = 0) : A(_A), g(_g) {}

    bool operator< (const Node& rhs) const {
        return A < rhs.A;
    }
};

typedef set<Node>::iterator sit;

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);

    while(kase--) {
        scanf("%d", &n);
        init();

        _for(i, 0, n) scanf("%d", &a[i]);
        if(n == 1) {
            printf("1\n");
            continue;
        }

        initCal();

        // init calculate f() and g()
        // then solve
        set<Node> tb;
        tb.clear();
        tb.insert(Node(a[0], g[0]));

        int ans = 1;
        _for(i, 1, n) {
            Node cur(a[i], g[i]);
            sit it = tb.lower_bound(cur);

            bool keep = true;
            if(it != tb.begin()) {
                Node last = *(--it);
                int len = last.g + f[i];
                ans = max(ans, len);
                if(cur.g <= last.g) keep = false;
            }

            if(keep) {
                tb.erase(cur);
                tb.insert(cur);

                it = tb.find(cur);
                it++;

                while(it != tb.end() && (it->A > cur.A && it->g <= cur.g)) tb.erase(it++);
            }
        }
        cout << ans << endl;
    }
}