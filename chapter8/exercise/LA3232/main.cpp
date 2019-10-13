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

typedef vector<int>::iterator vii;
const int maxn = 5000 + 10;

vector<int> H[maxn], L[maxn];
int N[maxn];
int n;

void init() {
    _for(i, 0, maxn) {
        H[i].clear();
        L[i].clear();
    }
    Set(N, 0);
}

bool find1(int p) {
    _for(i, 0, H[p].size()) {
        int q = H[p][i];

        vii rit = upper_bound(L[p].begin(), L[p].end(), q);
        if(rit == L[p].end()) continue;

        int r = *rit;

        vii sit = upper_bound(H[p].begin(), H[p].end(), r);
        while (sit != H[p].end()) {
            int s = *sit;

            if(binary_search(L[q].begin(), L[q].end(), s)) return true;

            sit++;
        }
    }
    return false;
}

bool find2(int p) {
    _for(i, 0, L[p].size()) {
        int q = L[p][i];

        vii rit = upper_bound(H[p].begin(), H[p].end(), q);
        if(rit == H[p].end()) continue;

        int r = *rit;

        vii sit = upper_bound(L[p].begin(), L[p].end(), r);
        while (sit != L[p].end()) {
            int s = *sit;

            if(binary_search(H[q].begin(), H[q].end(), s)) return true;

            sit++;
        }
    }
    return false;
}

bool solve() {
    _for(i, 0, n) if(find1(i) || find2(i)) return true;
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    while (T--) {
        init();
        scanf("%d", &n);
        _for(i, 0, n) scanf("%d", &N[i]);

        _for(i, 0, n) _for(j, i + 1, n) {
            if(N[j] > N[i]) H[i].push_back(j);
            else if(N[j] < N[i]) L[i].push_back(j);
        }

        if(solve()) printf("YES\n");
        else printf("NO\n");
    }
}