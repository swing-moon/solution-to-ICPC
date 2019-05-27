//
//  main.cpp
//  hiho1465
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

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define REP(i, l, r) for(int i = (l); i <= (r); i++)
#define FOR(i, l, r) for(int i = (l); i < (r); i++)
typedef long long llong;

using namespace std;
const int maxl = 1000000 + 10;
const int maxn = 2 * maxl;

int maxlen[maxn], endpos[maxn], link[maxn], vis[maxn];
int trans[maxn][26];
int last = 1, size = 1;

void init() {
    Set(maxlen, 0); Set(endpos, 0); Set(link, 0); Set(vis, 0);
    Set(trans, 0);
}

inline void extend(int ch) {
    //
    int p = last, cur = ++size;
    maxlen[cur] = maxlen[p] + 1;
    endpos[cur] = 1;
    
    for(; p && !trans[p][ch]; p = link[p]) trans[p][ch] = cur;
    // relink cur
    if(!p) link[cur] = 1;
    else {
        int q = trans[p][ch];
        if(maxlen[p] + 1 == maxlen[q]) link[cur] = q;
        else {
            int clone = ++size;
            endpos[clone] = 0;
            maxlen[clone] = maxlen[p] + 1;
            Cpy(trans[clone], trans[q]); link[clone] = link[q];
            for(; p && trans[p][ch] == q; p = link[p]) trans[p][ch] = clone;
            link[cur] = link[q] = clone;
        }
    }
    
    last = cur;
}

int cnt[maxn], sa[maxn];
inline void topo() {
    for(int i = 1; i <= size; i++) cnt[maxlen[i]]++;
    for(int i = 1; i <= size; i++) cnt[i] += cnt[i-1];
    for(int i = size; i; i--) sa[cnt[maxlen[i]]--] = i;
    for(int i = size; i; i--) endpos[link[sa[i]]] += endpos[sa[i]];
}

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
        if(trans[u][ch]) { u = trans[u][ch]; lcs++; }
        else {
            for(; u && !trans[u][ch]; u = link[u]);
            if(!u) { u = 1; lcs = 0; }
            else {
                lcs = maxlen[u] + 1;
                u = trans[u][ch];
            }
        }
        
        if(lcs > base) {
            while(maxlen[link[u]] >= base) { u = link[u]; lcs = maxlen[u]; }
        }
        // find most early suffix which is satisfied l >= n
        
        if(lcs >= base && version[u] != num) {
            version[u] = num;
            ans += endpos[u];
        }
    }
    return ans;
}

string str;

int main() {
    freopen("input.txt", "r", stdin);
    //scanf("%s", str);
    init();
    cin >> str;
    for(int i = 0; i < str.length(); i++) extend(str[i] - 'a');
    topo();
    
    int kase;
    scanf("%d", &kase);
    for(int k = 1; k <= kase; k++) {
        cin >> str;
        llong res = solve(str, k);
        printf("%lld\n", res);
    }
}
