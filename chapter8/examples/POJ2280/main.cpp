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

const int maxn = 1000 + 10;

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

int n;

class Point {
public:
    int x, y;
    double deg;

    bool operator< (const Point& rhs) const {
        return deg < rhs.deg;
    }
};

Point mol[maxn], pt[maxn];
int color[maxn];

void init() {
    Set(color, 0);
}

bool det(const Point& A, const Point& B) {
    return A.x * B.y - A.y * B.x >= 0;
}

int solve() {
    if(n <= 2) return 2;

    int ans = 0;

    // update ans
    // i as pivot
    _for(i, 0, n) {
        int k = 0;

        _for(j, 0, n) {
            if(j == i) continue;
            pt[k].x = mol[j].x - mol[i].x;
            pt[k].y = mol[j].y - mol[i].y;
            if(color[j]) {
                pt[k].x = -pt[k].x;
                pt[k].y = -pt[k].y;
            }
            pt[k].deg = atan2(pt[k].y, pt[k].x);

            k++;
        }
        // i as pivot, original point
        // all nodes relative coordinates => pt[0, k)

        sort(pt, pt + k);

        int R = 0, cnt = 2;
        _for(L, 0, k) {
            if(R == L) {
                R = (R + 1) % k;
                cnt++;
            }

            while(R != L && det(pt[L], pt[R])) {
                R = (R + 1) % k;
                cnt++;
            }

            cnt--;
            ans = max(ans, cnt);
        }
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    while(scanf("%d", &n) == 1 && n) {
        init();
        _for(i, 0, n) scanf("%d%d%d", &mol[i].x, &mol[i].y, &color[i]);

        printf("%d\n", solve());
    }
}