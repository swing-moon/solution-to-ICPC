
//
//  main.cpp
//  hiho1457
//
//  Created by zhangmin chen on 2019/2/23.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define REP(i, l, r) for(int i = (l); i <= (r); i++)
#define FOR(i, l, r) for(int i = (l); i < (r); i++)
typedef long long llong;

using namespace std;
const int maxl = 1000000 + 10;
const int maxn = 2 * maxl;
const llong MOD = 1000000007;


struct SAM {
    int maxlen[maxn], trans[maxn][26], link[maxn], size, last;
    SAM() {
        Set(maxlen, 0); Set(trans, 0); Set(link, 0);
        size = last = 1;
    }
    
    void extend(int ch) {
        int cur = ++size, p = last;
        maxlen[cur] = maxlen[p] + 1;
        
        for(; p && !trans[p][ch]; p = link[p]) trans[p][ch] = cur;
        
        if(!p) link[cur] = 1;
        else {
            int q = trans[p][ch];
            if(maxlen[p] + 1 == maxlen[q]) link[cur] = q;
            else {
                int clone = ++size;
                maxlen[clone] = maxlen[p] + 1;
                Cpy(trans[clone], trans[q]); link[clone] = link[q];
                
                for(; p && trans[p][ch] == q; p = link[p]) trans[p][ch] = clone;
                link[cur] = link[q] = clone;
            }
        }
        last = cur;
    }
};

SAM sam;

const int spc = 10;
int indeg[maxn];
llong cnt[maxn], val[maxn];


int main() {
    freopen("input.txt", "r", stdin);
    // llong ans = 0;
    Set(cnt, 0); Set(val, 0); Set(indeg, 0);
    int n;
    scanf("%d", &n);
    
    string str;
    while(n--) {
        cin >> str;
        for(int i = 0; i < str.length(); i++) sam.extend(str[i]-'0');
        if(n != 0) sam.extend(10);
    }
    
    queue<int> que; que.push(1); cnt[1] = 1;
    REP(i, 1, sam.size) REP(j, 0, spc) ++indeg[sam.trans[i][j]];
    
    while(!que.empty()) {
        int u = que.front(); que.pop();
        REP(i, 0, spc) {
            int v = sam.trans[u][i]; if(!v) continue;
            if(i != 10) {
                (cnt[v] += cnt[u]) %= MOD;
                (val[v] += val[u] * 10 % MOD + (llong)(i * cnt[u] % MOD)) %= MOD;
            }
            if(!(--indeg[v])) que.push(v);
        }
    }
    llong ans = 0;
    for(int i = 1; i <= sam.size; i++) ans = (ans + val[i]) % MOD;
    printf("%lld\n", ans);
}
