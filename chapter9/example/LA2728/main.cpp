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

const int maxt = 200 + 5;
const int maxn = 50 + 5;
const int inf = 0x3f3f3f3f;
int T, N;

int f[maxt][maxn];
int t[maxn];
int M1, M2;
int d[maxn], e[maxn];

int hasTrain[maxt][maxn][2];

void initdp() {
    Set(f, inf);
    f[T][N] = 0;
}

void initTrain() {
    Set(hasTrain, 0);

    _rep(i, 1, M1) {
        int st = d[i];
        hasTrain[d[i]][1][0] = 1;

        int j = 1;
        _rep(k, 1, N - 1) {
            st += t[k];
            if (st <= T) hasTrain[st][++j][0] = 1;
        }
    }

    _rep(i, 1, M2) {
        int st = e[i];
        hasTrain[st][N][1] = 1;

        int j = N;
        _forDown(k, N - 1, 1) {
            st += t[k];
            if(st <= T) hasTrain[st][--j][1] = 1;
        }
    }
}

void dp() {
    initTrain();
    initdp();

    _forDown(i, T - 1, 0) _rep(j, 1, N) {
        f[i][j] = f[i + 1][j] + 1;

        if(hasTrain[i][j][0] && j + 1 <= N && i + t[j] <= T) {
            f[i][j] = min(f[i][j], f[i + t[j]][j + 1]);
        }

        if(hasTrain[i][j][1] && j - 1 >= 1 && i + t[j - 1] <= T) {
            f[i][j] = min(f[i][j], f[i + t[j - 1]][j - 1]);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 1;

    while (scanf("%d", &N) && N) {
        scanf("%d", &T);

        _rep(i, 1, N - 1) scanf("%d", &t[i]);
        scanf("%d", &M1);
        _rep(i, 1, M1) scanf("%d", &d[i]);
        scanf("%d", &M2);
        _rep(i, 1, M2) scanf("%d", &e[i]);


        printf("Case Number %d: ", kase++);

        // solve the problem:
        dp();
        if(f[0][1] >= inf) printf("impossible");
        else cout << f[0][1];

        puts("");
    }
}