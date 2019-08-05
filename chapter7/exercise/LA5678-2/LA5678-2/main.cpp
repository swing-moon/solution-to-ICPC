//
//  main.cpp
//  LA5678-2
//
//  Created by zhangmin chen on 2019/7/12.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

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

using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;

const int UNIT = 5;
const int MAXN = 20 + 5;
const int MAXTASK = 10;

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

bitset<MAXN> units[UNIT], MASK;
vector<int> skip;
int N;

// units in overall scope means incoming task
// parameter *tb is old task

void init() {
    _for(i, 0, UNIT) units[i].reset();
    // MASK.reset();
    skip.clear();
}

bool overlap(bitset<MAXN>* tb, int dt) {
    _for(i, 0, UNIT) if( ((tb[i] << dt) & units[i]).any() ) return true;
    return false;
}

void read() {
    char line[MAXN];
    _for(i, 0, UNIT) {
        scanf("%s", line);
        _for(j, 0, N) if(line[j] == 'X') units[i].set(j);
    }
    _rep(dt, 1, N) if(!overlap(units, dt)) skip.push_back(dt);
    // MASK = (1 << N) - 1;
}

void dfs(bitset<MAXN>* tb, int clock, int d, int& ans) {
    if(d == MAXTASK) {
        ans = min(ans, clock);
        return;
    }
    
    if( (clock + (MAXTASK - d) * skip[0]) > ans) return;
    
    _for(i, 0, skip.size()) {
        int dt = skip[i];
        if(!overlap(tb, dt)) {
            bitset<MAXN> nxt[UNIT];
            _for(j, 0, UNIT) nxt[j] = tb[j];
            
            _for(j, 0, UNIT) nxt[j] = ((nxt[j] << dt) | units[j]);
            
            dfs(nxt, clock + dt, d + 1, ans);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &N) && N) {
        //
        init();
        read();
        int ans = N * MAXTASK;
        dfs(units, N, 1, ans);
        printf("%d\n", ans);
    }
}
