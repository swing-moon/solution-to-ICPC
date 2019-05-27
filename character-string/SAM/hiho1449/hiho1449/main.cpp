//
//  main.cpp
//  hiho1449
//
//  Created by zhangmin chen on 2019/2/22.
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

llong cnt[maxn];
struct SAM {
    int maxlen[maxn], trans[maxn][26], link[maxn], size, last;
    SAM() {
        Set(maxlen, 0); Set(trans, 0); Set(link, 0);
        size = last = 1;
    }
    
    void extend(int ch) {
        //
        int cur = ++size, p = last;
        maxlen[cur] = maxlen[p] + 1;
        cnt[cur] = 1;
        
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
char str[maxl];

vector<int> G[maxn];
int indeg[maxn];
llong ans[maxn];

void build() {
    REP(i, 1, sam.size) { G[i].push_back(sam.link[i]); indeg[sam.link[i]]++; }
}

void topo() {
    queue<int> que;
    build();
    REP(i, 0, sam.size) if(!indeg[i]) que.push(i);
    
    while(!que.empty()) {
        int u = que.front(); que.pop();
        for(int v : G[u]) {
            // ans[sam.maxlen[u]] = max(ans[sam.maxlen[u]], cnt[u]);
            cnt[v] += cnt[u];
            if(!(--indeg[v])) que.push(v);
        }
    }
    REP(i, 1, sam.size) ans[sam.maxlen[i]] = max(ans[sam.maxlen[i]], cnt[i]);
    // FOR(i, 1, sam.size) debug(cnt[i]);
}

int main() {
    //
    freopen("input.txt", "r", stdin);
    string str;
    cin >> str;
    for(int i = 0; i < str.length(); i++) sam.extend(str[i] - 'a');
    
    topo();
    for(int i = (int)str.length(); i >= 1; i--) ans[i] = max(ans[i], ans[i+1]);
    for(int i = 1; i <= str.length(); i++) cout << ans[i] << endl;
}
