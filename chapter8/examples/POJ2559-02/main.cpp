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

class Rec {
public:
    int h, w;
    Rec(int _h = 0, int _w = 0) : h(_h), w(_w) {}

};

int n;
Rec recs[maxn];
llong ans;

stack<Rec> stk;

void init() {
    ans = 0;
    while(!stk.empty()) stk.pop();
}

int main() {
    freopen("input.txt", "r", stdin);
    while (cin >> n && n) {
        init();

        stk.push(Rec(0, 0));
        _rep(i, 1, n + 1) {
            int x;
            if(i == n + 1) x = 0;
            else scanf("%d", &x);

            if(stk.top().h < x) stk.push(Rec(x, 1));
            else {
                int width = 0;
                while (stk.top().h > x) {
                    width += stk.top().w;
                    ans = max(ans, (llong)width * stk.top().h);
                    stk.pop();
                }
                stk.push(Rec(x, width + 1));
            }
        }
        cout << ans << endl;
    }
}