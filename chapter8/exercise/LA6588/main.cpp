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
int n, arr[maxn];

vector<pair<int, int> > vec;

void init() {
    Set(arr, 0);
    vec.clear();
}

int Find(int x) {
    _rep(i, 1, n) if(arr[i] == x) return i;
    return -1;
}

void swapSeg(int from, int to) {
    // [from, to]
    int len = to - from + 1;
    _for(i, 0, len / 2) swap(arr[from + i], arr[from + len / 2 + i]);

    vec.push_back(make_pair(from, to));
}

void solve() {
    _rep(i, 1, n) {
        if(arr[i] == i) continue;
        int pos = Find(i);
        int to = i + (pos - i) * 2 - 1;

        while (to > n) {
            int len = pos - i + 1;
            if(len % 2) swapSeg(i + 1, pos);
            else swapSeg(i, pos);

            pos = Find(i);
            to = i + (pos - i) * 2 - 1;
        }
        swapSeg(i, to);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);

    while (kase--) {
        init();
        scanf("%d", &n);
        _rep(i, 1, n) scanf("%d", &arr[i]);

        solve();
        printf("%lu\n", vec.size());
        _for(i, 0, vec.size()) printf("%d %d\n", vec[i].first, vec[i].second);
    }
}