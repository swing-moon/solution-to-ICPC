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

const double pi = acos(-1);

class Circle {
public:
    int r, x, y;
    Circle(int _r = 0, int _x = 0, int _y = 0) : r(_r), x(_x), y(_y) {}

    bool operator< (const Circle& rhs) const {
        if(r != rhs.r) return r < rhs.r;
        if(x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
};

ostream& operator<< (ostream& os, const Circle& c) {
    char buf[128];
    sprintf(buf, " (%d,%d,%d)", c.r, c.x, c.y);
    return os << buf;
}

bool inRange(int x, int l, int r) {
    if(l > r) return inRange(x, r, l);
    return l <= x && x <= r;
}

vector<string> lines;
vector<Circle> ans;

void init() {
    lines.clear();
    ans.clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    _rep(kase, 1, T) {
        init();

        int w, h;
        scanf("%d%d", &w, &h);

        lines.resize(h);
        _for(i, 0, h) cin >> lines[i];

        // then we solve the problem
        _rep(r, 5, 50) _rep(x, r, w - r) _rep(y, r, h - r) {
            int tot = 0, black = 0;

            // then enumerate
            _for(i, 0, 100) {
                double deg = 2 * pi * (rand() / (RAND_MAX + 1.0));
                int cx = (int)(x + r * cos(deg) + 0.5), cy = (int)(y + r * sin(deg) + 0.5);

                if(inRange(cx, 0, w - 1) && inRange(cy, 0, h - 1) && lines[cy][cx] == '1') black++;
                tot++;

                if(tot > 10 && black * 2 < tot) break;
            }

            if(black / (double) tot > 0.8) ans.push_back(Circle(r, x, y));
        }

        printf("Case %d: ", kase);
        cout << ans.size();
        _for(i, 0, ans.size()) cout << ans[i];
        cout << endl;
    }
}