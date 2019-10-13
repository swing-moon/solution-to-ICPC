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

const int maxl = 250005;
const int maxn = maxl * 2;


class SAM {
public:
    int sz, last;
    int trans[maxn][26], link[maxn], maxlen[maxn];

    SAM() {
        Set(trans, 0);
        Set(link, 0);
        Set(maxlen, 0);

        sz = last = 1;
    }

    void extend(int ch) {
        int cur = ++sz, p = last;
        maxlen[cur] = maxlen[p] + 1;

        for( ; p && trans[p][ch] == 0; p = link[p]) trans[p][ch] = cur;

        if(p == 0) link[cur] = 1;
        else {
            int q = trans[p][ch];
            if(maxlen[p] + 1 == maxlen[q]) link[cur] = q;
            else {
                int clone = ++sz;
                maxlen[clone] = maxlen[p] + 1;

                Cpy(trans[clone], trans[q]);
                link[clone] = link[q];

                for( ; p && trans[p][ch] == q; p = link[p]) trans[p][ch] = clone;
                link[q] = link[cur] = clone;
            }
        }

        last = cur;
    }

    int LCS(const char* str) {
        int len = strlen(str);
        int lcs = 0, tmplen = 0;
        int cur = 1;

        _for(i, 0, len) {
            int x = str[i] - 'a';
            if(trans[cur][x]) {
                cur = trans[cur][x];
                tmplen++;
            }
            else {
                while (cur && trans[cur][x] == 0) cur = link[cur];
                if(cur) {
                    tmplen = maxlen[cur] + 1;
                    cur = trans[cur][x];
                }
                else {
                    tmplen = 0;
                    cur = 1;
                }
            }
            lcs = max(lcs, tmplen);
        }
        return lcs;
    }
};

SAM sam;

int main() {
    freopen("input.txt", "r", stdin);
    char A[maxl], B[maxl];
    scanf("%s%s", A, B);
    int lenA = strlen(A), lenB = strlen(B);

    _for(i, 0, lenA) sam.extend(A[i] - 'a');
    cout << sam.LCS(B) << endl;

}