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

const int maxn = 100 + 5;
int f[maxn][maxn];
int N;
char str[maxn];

void init() {
    N = strlen(str);
}

void initdp() {
    Set(f, -1);
    _for(i, 0, N) {
        f[i + 1][i] = 0;
        f[i][i] = 1;
    }
}

bool match(char a, char b) {
    return (a == '(' && b == ')') || (a == '[' && b == ']');
}

void dp() {
    for(int i = N - 2; i >= 0; i--) {
        _for(j, i + 1, N) {
            f[i][j] = N;
            if(match(str[i], str[j])) f[i][j] = min(f[i][j], f[i + 1][j - 1]);

            _for(k, i, j) f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
        }
    }
}

void print(int i, int j) {
    if(i > j) return;
    if(i == j) {
        if(str[i] == '(' || str[i] == ')') printf("()");
        else printf("[]");
        return;
    }

    if(match(str[i], str[j]) && f[i][j] == f[i + 1][j - 1]) {
        printf("%c", str[i]);
        print(i + 1, j - 1);
        printf("%c", str[j]);
        return;
    }

    _for(k, i, j) {
        if(f[i][j] == f[i][k] + f[k + 1][j]) {
            print(i, k);
            print(k + 1, j);
            return;
        }
    }
}

void read(char* str) {
    fgets(str, maxn, stdin);
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    getchar();

    while (T--) {
        read(str);
        read(str);
        if(str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';
        init();
        //debug(N);

        initdp();
        dp();
        print(0, N - 1);
        cout << endl;

        if(T) cout << endl;
    }
}