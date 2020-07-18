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

const int maxn = 80 + 5;
char A[maxn], B[maxn];
int N = 0, M = 0;
const int inf = 0x3f3f3f3f;

int f[maxn][maxn];
int locA[maxn][26], locB[maxn][26];
vector<string> res;



void initdp() {
    Set(f, 0);
    Set(locA, 0);
    Set(locB, 0);
    assert(N != 0);
    res.clear();

    _rep(i, 1, N) {
        _for(ch, 0, 26) {
            if(A[i] - 'a' == ch) locA[i][ch] = i;
            else locA[i][ch] = locA[i - 1][ch];
        }
    }

    _rep(i, 1, M) {
        _for(ch, 0, 26) {
            if(B[i] - 'a' == ch) locB[i][ch] = i;
            else locB[i][ch] = locB[i - 1][ch];
        }
    }
}

int dp() {
    _rep(i, 1, N) _rep(j, 1, M) {
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            if(A[i] == B[j]) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
        }
    return f[N][M];
}

void dfs(int x, int y, int len, string str) {
    if(len == 0) {
        res.push_back(str);
        return;
    }
    if(!x || !y) return;

    _for(ch, 0, 26) {
        int l1 = locA[x][ch], l2 = locB[y][ch];
        if(f[l1][l2] != len) continue;

        dfs(l1 - 1, l2 - 1, len - 1, char(ch + 'a') + str);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%s", A + 1);
    scanf("%s", B + 1);
    N = strlen(A + 1), M = strlen(B + 1);
    //debug(N), debug(M);

    initdp();
    int len = dp();
    //debug(ans);
    string str;
    dfs(N, M, len, str);

    sort(res.begin(), res.end());
    _for(i, 0, res.size()) cout << res[i] << endl;
}