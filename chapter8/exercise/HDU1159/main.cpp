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
typedef vector<int>::iterator vii;


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

const int maxn = 1000 + 5;
char A[maxn], B[maxn];

vector<int> loc[maxn];
vector<int> C, D;

void init() {
    _for(i, 0, maxn) loc[i].clear();
    C.clear();
    D.clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%s%s", A, B) != EOF) {
        init();

        int lenA = strlen(A), lenB = strlen(B);


        _forDown(i, lenB - 1, 0) loc[B[i] - 'a'].push_back(i);
        _for(i, 0, lenA) {
            int x = A[i] - 'a';
            if(loc[x].empty()) continue;
            _for(j, 0, loc[x].size()) {
                C.push_back(loc[x][j]);
            }
        }

        if(!C.empty()) {
            D.push_back(C[0]);
            _for(i, 1, C.size()) {
                if(C[i] > D.back()) D.push_back(C[i]);
                else {
                    vii it = lower_bound(D.begin(), D.end(), C[i]);
                    *it = C[i];
                }
            }
        }

        cout << D.size() << endl;
    }
}