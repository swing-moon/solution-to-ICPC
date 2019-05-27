//
//  main.cpp
//  hiho1466
//
//  Created by zhangmin chen on 2019/2/28.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
typedef long long llong;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define REP(i, l, r) for(int i = (l); i <= (r); i++)
#define FOR(i, l, r) for(int i = (l); i < (r); i++)

const int maxl = 100000 + 10;
const int maxn = 2*maxl;
const int N = 27;

// cnt(pre, SG())

struct SAM {
    int len[maxn], trans[maxn][26], link[maxn], size, last;
    // other arr[]
    int sg[maxn];
    llong cnt[maxn][N+1];
    
    SAM() {
        Set(len, 0); Set(trans, 0); Set(link, 0);
        Set(sg, -1);
        size = 1;
        last = 1;
    }
    
    void extend(int ch) {
        int cur = ++size, p = last;
        // 1 is the " "
        
        len[cur] = len[p] + 1;
        //debug(cur);
        
        for(; p && !trans[p][ch]; p = link[p]) trans[p][ch] = cur;
        // relink cur
        
        
        if(!p) link[cur] = 1;
        else {
            int q = trans[p][ch];
            if(len[p] + 1 == len[q]) link[cur] = q;
            else {
                int clone = ++size;
                len[clone] = len[p] + 1;
                Cpy(trans[clone], trans[q]); link[clone] = link[q];
                
                for(; p && trans[p][ch] == q; p = link[p]) trans[p][ch] = clone;
                link[cur] = link[q] = clone;
            }
        }
        last = cur;
    }
    
    int SG(int x) {
        if(sg[x] != -1) return sg[x];
        bool flag[28];
        for(int i = 0; i < 27; i++) flag[i] = 0;
        
        for(int i = 0; i < 26; i++) {
            int to = trans[x][i];
             //debug(to);
            
            if(to == 0) continue;
            flag[SG(to)] = 1;
            for(int j = 0; j < 27; j++) cnt[x][j] += cnt[to][j];
            // I made a bug here, is j
        }
        
        for(int i = 0; i < 27; i++) if(!flag[i]) {
            sg[x] = i; break;
        }
        cnt[x][sg[x]]++;
        for(int i = 0; i < 27; i++) cnt[x][27] += cnt[x][i];
        
        return sg[x];
    }
    
    void Debug() {
        for(int i = 0; i <= size; i++) {
            printf("i: %d:\n", i);
            for(int j = 0; j < 28; j++) /*printf("%lld ", cnt[i][j]);*/ debug(cnt[i][j]);
            printf("sg:: %d\n", sg[i]);
            
            /*
            for(int j = 0; j < 26; j++)
                debug(trans[i][j]);
             
             */
        }
    }
    
};

SAM A, B;
char res[2][maxn];

llong k;
// cntA[u][sg()]    cntB[v][sg()]
// (sa_u, sb_v)
llong cost(int u, int v) {
    llong ans = 0;
    for(int i = 0; i < 27; i++)
        ans += 1LL * A.cnt[u][i] * (B.cnt[v][27] - B.cnt[v][i]);
    return ans;
}


// p is the item of resA[p]
// A.sg[x]   x = {_, a, b, ab}

int dfsA(int p, int x) {
    llong ct = B.cnt[1][27] - B.cnt[1][A.sg[x]];
    //debug(ct);
    //debug(k);
    
    //cout << endl;
    
    // B from 0 to match
    
    if(k <= ct) return x;
    else {
        k -= ct;
        for(int i = 0; i < 26; i++) {
            int to = A.trans[x][i];
            if(to == 0) continue;
            //debug(to);
            
            llong ct2 = cost(to, 1);
            if(ct2 < k) k -= ct2;
            else {
                res[0][p] = 'a' + i;
                return dfsA(p+1, to);
                // return dfsA(next)
            }
        }
        return -1;
    }
    
    /*
    // follow the path in SAM
    for(int i = 0; i < 26; i++) {
        int to = A.trans[x][i];
        if(to == 0) continue;
        
        llong ct2 = cost(to, 1);
        if(ct2 < k) k -= ct2;
        else {
            // ct2 >= k, we follow the path and extend char
            // to reduce ct2
            
            res[0][p] = 'a' + i;
            debug(res[0]);
            dfsA(p+1, to);
        }
    }
    if(k > ct) return -1;
    else return x;
     */
}


void dfsB(int p, int x, int T) {
    k -= A.sg[T] != B.sg[x];
    if(k == 0) return;
    
    for(int i = 0; i < 26; i++) {
        int to = B.trans[x][i];
        if(to == 0) continue;
        
        llong ct = B.cnt[to][27] - B.cnt[to][A.sg[T]];
        if(ct < k) k -= ct;
        else {
            // reduce ct
            res[1][p] = 'a' + i;
            dfsB(p+1, to, T);
            return;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    string a, b;
    cin >> k;
    cin >> a >> b;
    
    //debug(a[0]);
    
    for(int i = 0; i < a.length(); i++) A.extend(a[i] - 'a');
    A.SG(1);
    //A.Debug();
    for(int i = 0; i < b.length(); i++) B.extend(b[i] - 'a');
    B.SG(1);
    //B.Debug();
    
    
    int T = dfsA(0, 1);
    //debug(T);
    if(T == -1) {
        printf("NO\n");
        return 0;
    }
    
    dfsB(0, 1, T);
    puts(res[0]);
    puts(res[1]);
}
