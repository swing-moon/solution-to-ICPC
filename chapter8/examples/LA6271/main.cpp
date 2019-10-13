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

const int maxn = 1024 + 5;
char G[maxn][maxn];
int n;

// vector<int> win, gray point; vector<int> lose, black point
void solve() {
    vector<int> win, lose;
    _rep(i, 2, n) {
        if(G[1][i] == '1') win.push_back(i);
        else lose.push_back(i);
    }

    int rnd = n;
    while (rnd > 1) {
        vector<int> win2, lose2, last;

        // phase 1
        _for(i, 0, lose.size()) {
            int _lose = lose[i];
            bool matched = false;

            _for(j, 0, win.size()) {
                int& _win = win[j];
                if(_win > 0 && G[_win][_lose] == '1') {
                    printf("%d %d\n", _win, _lose);
                    win2.push_back(_win);
                    _win = 0;
                    matched = true;
                    break;
                }
            }

            if(!matched) last.push_back(_lose);
        }

        // phase 2
        bool first = true;
        _for(i, 0, win.size()) {
            int _win = win[i];
            if(_win > 0) {
                if(first) {
                    printf("1 %d\n", _win);
                    first = false;
                }
                else last.push_back(_win);
            }
        }

        // phase 3
        for(int i = 0; i < last.size(); i += 2) {
            printf("%d %d\n", last[i], last[i + 1]);
            int keep = last[i];
            if(G[last[i + 1]][keep] == '1') keep = last[i + 1];
            if(G[1][keep] == '1') win2.push_back(keep);
            else lose2.push_back(keep);
        }

        win = win2;
        lose = lose2;
        rnd >>= 1;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    while(scanf("%d", &n) == 1) {
        _rep(i, 1, n) scanf("%s", G[i] + 1);

        // input finished
        solve();
    }
}