//
//  main.cpp
//  uva11107
//
//  Created by zhangmin chen on 2019/2/16.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1001 * 100 + 10;

struct suffixArray {
    int str[maxn], sa[maxn], rank[maxn], lcp[maxn];
    int c[maxn], t1[maxn], t2[maxn];
    int n;
    
    void init() { n = 0; memset(sa, 0, sizeof(sa)); }
    
    void buildSa(int Rdx) {
        int i, *x = t1, *y = t2;
        for(i = 0; i < Rdx; i++) c[i] = 0;
        for(i = 0; i < n; i++) c[x[i] = str[i]]++;
        for(i = 1; i < Rdx; i++) c[i] += c[i-1];
        for(i = n-1; i >= 0; i--) sa[--c[x[i]]] = i;
        
        for(int offset = 1; offset <= n; offset <<= 1) {
            int p = 0;
            for(i = n-offset; i < n; i++) y[p++] = i;
            for(i = 0; i < n; i++) if(sa[i] >= offset) y[p++] = sa[i] - offset;
            
            // radix sort
            for(i = 0; i < Rdx; i++) c[i] = 0;
            for(i = 0; i < n; i++) c[x[y[i]]]++;
            for(i = 1; i < Rdx; i++) c[i] += c[i-1];
            for(i = n-1; i >= 0; i--) { sa[--c[x[y[i]]]] = y[i]; y[i] = 0; }
            
            // rebuild x and y
            swap(x, y); x[sa[0]] = 0; p = 1;
            for(i = 1; i < n; i++)
                x[sa[i]] = y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+offset] == y[sa[i]+offset] ? p-1 : p++;
            if(p >= n) break;
            Rdx = p;
        }
    }
    
    void getLcp() {
        int k = 0;
        for(int i = 0; i < n; i++) rank[sa[i]] = i;
        for(int i = 0; i < n; i++) {
            if(rank[i] == 0) continue;
            if(k) k--;
            
            int j = sa[rank[i] - 1];
            while(str[i+k] == str[j+k]) k++;
            lcp[rank[i]] = k;
        }
    }
};


const int maxl = 1000 + 10;
const int maxc = 100 + 10;

suffixArray sa;
int n;
char word[maxl];
int flag[maxc];
int idx[maxn];

void add(int ch, int wid) {
    // add alpha in sa
    idx[sa.n] = wid;
    sa.str[sa.n++] = ch;
}

bool judge(int left, int right) {
    memset(flag, 0, sizeof(flag));
    if(right-left <= n/2) return false;
    int cnt = 0;
    for(int i = left; i < right; i++) {
        int wid = idx[sa.sa[i]];
        if(wid != n && flag[wid] == 0) { flag[wid] = 1; cnt++; }
    }
    return cnt > n/2;
}

void printSub(int l, int r) {
    for(int i = l; i < r; i++) {
        printf("%c", sa.str[i]-1+'a');
    }
    printf("\n");
}

bool okForLength(int len, bool print) {
    // binary search
    int left = 0;
    for(int right = 1; right <= sa.n; right++) if(right == sa.n || sa.lcp[right] < len) {
        // a new block
        if(judge(left, right)) {
            if(print) printSub(sa.sa[left], sa.sa[left]+len);
            // is sa.sa[left], printout original str[]
            else return true;
        }
        
        left = right;
    }
    return false;
}


void solve(int maxlen) {
    //
    if(!okForLength(1, false)) printf("?\n");
    else {
        int l = 1, r = maxlen, mid;
        while(l < r) {
            mid = l + (r-l+1)/2;
            if(okForLength(mid, false)) l = mid;
            else r = mid-1;
        }
        okForLength(l, true);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;
    while(scanf("%d", &n) == 1 && n) {
        if(kase++ > 0) printf("\n");
        int maxlen = 0;
        sa.init();
        
        for(int i = 0; i < n; i++) {
            scanf("%s", word);
            int sz = (int)strlen(word);
            maxlen = max(maxlen, sz);
            
            for(int j = 0; j < sz; j++)
                add(word[j]-'a'+1, i);
            add(100+i, n);
        }
        add(0, n);
        
        if(n == 1) printf("%s\n", word);
        else {
            sa.buildSa(100+n);
            sa.getLcp();
            solve(maxlen);
        }
    }
    return 0;
}
