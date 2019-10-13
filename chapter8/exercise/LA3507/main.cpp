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

const int maxn = 800000 + 10;
int N;

class Ord {
public:
    int q, d;
    Ord(int _q = 0, int _d = 0) : q(_q), d(_d) {}

    bool operator< (const Ord& rhs) const {
        return d < rhs.d;
    }
};

Ord ords[maxn];

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    cin >> T;

    _for(t, 0, T) {
        if(t) puts("");

        cin >> N;
        _for(i, 0, N) cin >> ords[i].q >> ords[i].d;

        sort(ords, ords + N);

        int timing = 0;
        priority_queue<int> pq;

        _for(i, 0, N) {
            const Ord& cur = ords[i];

            if(timing + cur.q <= cur.d) {
                timing += cur.q;
                pq.push(cur.q);
            }
            else if(!pq.empty() && cur.q < pq.top()) {
                timing = timing - pq.top() + cur.q;
                pq.pop();
                pq.push(cur.q);
            }
        }

        cout << pq.size() << endl;
    }
}