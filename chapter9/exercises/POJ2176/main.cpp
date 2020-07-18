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

const int maxn = 100 + 10;
const int inf = 0x3f3f3f3f;
char str[maxn];
int N;

class Seg {
public:
    int plen;
    char pstr[maxn];
};

Seg f[maxn][maxn];

void init() {
    N = strlen(str + 1);
}

void initdp() {
    _rep(i, 1, N) {
        f[i][i].plen = 1;
        f[i][i].pstr[0] = str[i];
    }
}

void folding(int i, int j) {
    // fold str[i, j]
    int l = j - i + 1;
    _rep(ll, 1, l / 2) {
        if(l % ll) continue;

        int ii = i, jj = i + ll;
        while (str[ii] == str[jj] && jj <= j) ii++, jj++;

        if(jj > j) {
            // can fold
            // ll from [1, l / 2], try to find min fold
            // 2(A) is better than 1(AA)
            int cnt = l / ll;

            // str[i, i + ll - 1] is pattern substring
            sprintf(f[i][j].pstr, "%d", cnt);
            strcat(f[i][j].pstr, "(");
            strcat(f[i][j].pstr, f[i][i + ll - 1].pstr);
            strcat(f[i][j].pstr, ")");
            f[i][j].plen = strlen(f[i][j].pstr);

            break;
        }
    }
}

void dp() {
    _rep(len, 2, N) _rep(i, 1, N - len + 1) {
        int j = i + len - 1;
        f[i][j].plen = inf;

        folding(i, j);

        _for(k, i, j) {
            if(f[i][j].plen > f[i][k].plen + f[k + 1][j].plen) {
                f[i][j].plen = f[i][k].plen + f[k + 1][j].plen;
                strcpy(f[i][j].pstr, f[i][k].pstr);
                strcat(f[i][j].pstr, f[k + 1][j].pstr);
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%s", str + 1) != EOF) {
        init();
        initdp();
        dp();

        printf("%s\n", f[1][N].pstr);
    }
}