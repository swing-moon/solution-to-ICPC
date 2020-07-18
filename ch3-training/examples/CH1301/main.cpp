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

const int maxn = 100000 + 5;
int N;

class Node {
public:
    int x, k, pre, nxt;
    bool operator< (const Node& rhs) const {
        return x < rhs.x;
    }
};
Node A[maxn];
int B[maxn];

class Ans {
public:
    int x, k;
};
Ans ans[maxn];

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &N);
    _rep(i, 1, N) {
        scanf("%d", &A[i].x);
        A[i].k = i;
    }

    sort(A + 1, A + 1 + N);
    _rep(i, 1, N) {
        B[A[i].k] = i;
        A[i].pre = i - 1;
        A[i].nxt = i + 1;
    }

    int l = 1, r = N;
    _forDown(i, N, 1) {
        if(B[i] == r) {
            ans[i].x = A[r].x - A[A[r].pre].x;
            ans[i].k = A[A[r].pre].k;
            r = A[r].pre;
        }
        else if(B[i] == l) {
            ans[i].x = A[A[l].nxt].x - A[l].x;
            ans[i].k = A[A[l].nxt].k;
            l = A[l].nxt;
        }
        else {
            ans[i].x = A[A[B[i]].nxt].x - A[B[i]].x;
            ans[i].k = A[A[B[i]].nxt].k;
            if(A[B[i]].x - A[A[B[i]].pre].x <= ans[i].x) {
                ans[i].x = A[B[i]].x - A[A[B[i]].pre].x;
                ans[i].k = A[A[B[i]].pre].k;
            }
        }
        A[A[B[i]].pre].nxt = A[B[i]].nxt;
        A[A[B[i]].nxt].pre = A[B[i]].pre;
    }
    _rep(i, 2, N) printf("%d %d\n", ans[i].x, ans[i].k);
}