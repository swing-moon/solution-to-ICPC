//
//  main.cpp
//  hiho1445
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
        
        for(; p && !trans[p][ch]; p = link[p]) trans[p][ch] = cur;
        // then, we try to change the link of cur, link[cur] = ?
        
        if(!p) link[cur] = 1;
        else {
            int q = trans[p][ch];
            if(maxlen[p] + 1 == maxlen[q]) link[cur] = q;
            else {
                int clone = ++size;
                maxlen[clone] = maxlen[p] + 1;
                Cpy(trans[clone], trans[q]); link[clone] = link[q];
                
                for(; p && trans[p][ch] == q; p = link[p]) trans[p][ch] = clone;
                link[q] = link[cur] = clone;
            }
        }
        last = cur;
    }
};

SAM sam;
char str[maxl];

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%s", str);
    for(int i = 0; str[i]; i++) sam.extend(str[i] - 'a');
    llong ans = 0;
    
    for(int i = 1; i <= sam.size; i++) {
        if(i == 1) continue;
        ans += sam.maxlen[i] - sam.maxlen[sam.link[i]];
    }
    cout << ans;
}
