//
//  main.cpp
//  hiho1465-2
//
//  Created by zhangmin chen on 2019/2/25.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define REP(i, l, r) for(int i = (l); i <= (r); i++)
#define FOR(i, l, r) for(int i = (l); i < (r); i++)

typedef long long llong;
const int maxl = 1000000 + 10;
const int maxn = 2 * maxl;

struct SAM {
    int maxlen[maxn], trans[maxn][26], link[maxn], size, last;
    int tag[maxn], indeg[maxn], endpos[maxn];
    
    SAM() {
        Set(maxlen, 0); Set(trans, 0); Set(link, 0); Set(tag, 0);
        Set(indeg, 0); Set(endpos, 0);
        
        size = last = 1;
    }
    
    void extend(int ch) {
        int cur = ++size, p = last;
        tag[cur] = 1;
        maxlen[cur] = maxlen[p] + 1;
        
        for(; p && !trans[p][ch]; p = link[p]) trans[p][ch] = cur;
        // relink cur
        
        if(!p) link[cur] = 1;
        else {
            int q = trans[p][ch];
            if(maxlen[p] + 1 == maxlen[q]) link[cur] = q;
            else {
                int clone = ++size; tag[clone] = 0;
                maxlen[clone] = maxlen[p] + 1;
                Cpy(trans[clone], trans[q]); link[clone] = link[q];
                
                for(; p && trans[p][ch] == q; p = link[p]) trans[p][ch] = clone;
                link[cur] = link[q] = clone;
            }
        }
        last = cur;
    }
    
    void build() {
        for(int i = 1; i <= size; i++) ++indeg[link[i]];
        queue<int> que;
        for(int i = 1; i <= size; i++) if(indeg[i] == 0) {
            que.push(i); endpos[i] = 1;
        }
        
        while(!que.empty()) {
            int x = que.front(); que.pop();
            if(x == 0) continue;
            int y = link[x]; indeg[y]--;
            endpos[y] += endpos[x];
            
            if(indeg[y] == 0) {
                if(tag[y]) endpos[y]++;
                que.push(y);
            }
        }
    }
};

SAM sam;

int version[maxn];
llong solve(string& str, int num) {
    int len = (int)str.length(); int base = len;
    string str2 = str.substr(0, len-1);
    str += str2;
    len = 2*len - 1;
    
    int u = 1, lcs = 0;
    llong ans = 0;
    
    for(int i = 0; i < len; i++) {
        int ch = str[i] - 'a';
        if(sam.trans[u][ch]) { u = sam.trans[u][ch]; lcs++; }
        else {
            for(; u && !sam.trans[u][ch]; u = sam.link[u]);
            if(!u) { u = 1; lcs = 0; }
            else {
                lcs = sam.maxlen[u] + 1;
                u = sam.trans[u][ch];
            }
        }
        
        if(lcs > base) {
            while(sam.maxlen[sam.link[u]] >= base) { u = sam.link[u]; lcs = sam.maxlen[u]; }
        }
        if(lcs >= base && version[u] != num) {
            version[u] = num;
            ans += sam.endpos[u];
        }
    }
    return ans;
}


string str;

int main() {
    freopen("input.txt", "r", stdin);
    cin >> str;
    for(int i = 0; i < str.length(); i++) sam.extend(str[i] - 'a');
    sam.build();
    
    int kase;
    scanf("%d", &kase);
    for(int k = 1; k <= kase; k++) {
        cin >> str;
        llong res = solve(str, k);
        printf("%lld\n", res);
    }
}
