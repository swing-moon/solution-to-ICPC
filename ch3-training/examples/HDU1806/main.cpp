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
const int maxlog = 20;
int A[maxn];
int N, Q;

class RMQ {
public:
    int f[maxn][maxlog];
    void init(const vector<int>& A) {
        int n = A.size();;
        _for(i, 0, n) f[i][0] = A[i];
        for(int j = 1; (1<<j) <= n; j++) {
            for(int i = 0; i + (1<<j) - 1 < n; i++) {
                f[i][j] = max(f[i][j - 1], f[i + (1<<(j-1))][j - 1]);
            }
        }
    }

    int query(int L, int R) {
        int k = 0;
        while ((1<<(k+1)) <= R - L + 1) k++;
        return max(f[L][k], f[R-(1<<k)+1][k]);
    }
};

int _left[maxn], _right[maxn], idx[maxn];
vector<int> cnt;
// cnt[seg id]

void init() {
    Set(_left, 0);
    Set(_right, 0);
    Set(idx, 0);
    cnt.clear();
}

inline void cal(vector<int>& cnt) {
    int s = -1;
    _rep(i, 0, N) {
        if(i == 0 || A[i] > A[i-1]) {
            if(i > 0) {
                cnt.push_back(i - s);
                _for(k, s, i) {
                    idx[k] = cnt.size() - 1;
                    _left[k] = s;
                    _right[k] = i - 1;
                }
            }
            s = i;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &N, &Q) == 2) {
        _for(i, 0, N) scanf("%d", &A[i]);
        A[N] = A[N - 1] + 1;
        // special for RMQ

        init();
        cal(cnt);

        // then rmq
        RMQ rmq;
        rmq.init(cnt);

        // then query
        while (Q--) {
            int L, R, ans;
            scanf("%d%d", &L, &R);
            L--, R--;

            if(idx[L] == idx[R]) ans = R - L + 1;
            else {
                ans = max(_right[L] - L + 1, R - _left[R] + 1);
                if(idx[L] + 1 < idx[R]) ans = max(ans, rmq.query(idx[L] + 1, idx[R] - 1));
            }
            printf("%d\n", ans);
        }
    }
}