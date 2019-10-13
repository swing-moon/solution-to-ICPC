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

const int maxn = 500 + 10;
const int maxm = 2000 + 10;

int pa[maxn * 3];

void initPa(int n) {
    _rep(i, 0, n) pa[i] = i;
}
// usage: initPa(n * 3)
// self: x  lower: x + n   greater: x + n * 2

class Expr {
public:
    int x;
    char op;
    int y;
};

Expr expr[maxm];
int n, m;
int line[maxm];

void init() {
    Set(line, 0);
}

int find(int x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}


bool conflict(const Expr& expr) {
    int x = expr.x, y = expr.y;
    char op = expr.op;
    //debug(op);

    if(op == '>') {
        //puts("ok");
        if((find(x) == find(y)) || (find(x) == find(y + n * 2))) return 1;

        pa[find(x + n * 2)] = find(y);
        pa[find(x)] = find(y + n);
        pa[find(x + n)] = find(y + n * 2);
    }

    if(op == '<') {
        //puts("ok");
        if((find(x) == find(y)) || (find(x) == find(y + n))) return 1;

        pa[find(x + n)] = find(y);
        pa[find(x)] = find(y + n * 2);
        pa[find(x + n * 2)] = find(y + n);
    }

    if(op == '=') {
        //puts("ok");
        if((find(x) == find(y + n)) || (find(x + n) == find(y))) return 1;

        pa[find(x)] = find(y);
        pa[find(x + n)] = find(y + n);
        pa[find(x + n * 2)] = find(y + n * 2);
    }

    return 0;
}

void Rochambeau() {
    //
    _for(i, 0, m) scanf("%d%c%d", &expr[i].x, &expr[i].op, &expr[i].y);
    //debug(expr[0].op);

    init();

    int cnt = 0, id = 0;
    _for(i, 0, n) {
        // i is judge
        bool fail = 0;
        _rep(k, 0, n * 3) pa[k] = k;

        _for(j, 0, m) {
            Expr cur = expr[j];

            //debug(cur.x);
            //debug(cur.y);
            if(cur.x != i && cur.y != i && conflict(cur)) {
                fail = 1;
                if(j > line[i]) line[i] = j + 1;
                break;
            }
        }

        if(!fail) {
            id = i;
            cnt++;
        }
    }

    //debug(cnt);
    if(!cnt) puts("Impossible");
    else if(cnt == 1) {
        int ans = 0;
        _for(i, 0, n) if(line[i] > ans) ans = line[i];
        printf("Player %d can be determined to be the judge after %d lines\n", id, ans);
    }
    else puts("Can not determine");
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) != EOF) Rochambeau();
}