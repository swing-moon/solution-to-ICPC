//
//  main.cpp
//  LUOGU1972
//
//  Created by zhangmin chen on 2020/1/7.
//  Copyright © 2020 zhangmin chen. All rights reserved.
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
#define lowbit(i) (i & (-i))
#define MPR(a, b) make_pair(a, b)

const int maxn = 1000000 + 5;

class Fwick {
public:
    vector<int> C;
    int n;
    
    void resize(int n) {
        this->n = n;
        C.resize(n + 1);
    }
    
    void clear() {
        fill(C.begin(), C.end(), 0);
    }
    
    int sum(int x) {
        int ret = 0;
        while (x) {
            ret += C[x];
            x -= lowbit(x);
        }
        return ret;
    }
    
    void add(int x, int d) {
        while (x <= n) {
            C[x] += d;
            x += lowbit(x);
        }
        
        
    }
    
    int find(int l, int r, int val) {
        while (l < r) {
            int mid = (l + r) >> 1;
            if(sum(mid) < val) l = mid + 1;
            else r = mid;
        }
        return l;
    }
};

Fwick fwick;
int A[maxn], N, vis[maxn];
int ANS[maxn];
int m;


void init() {
    Set(vis, 0);
    Set(ANS, 0);
}

class Qry {
public:
    int l, r;
    int id;
    
    bool operator< (const Qry& rhs) const {
        return r < rhs.r;
    }
};
Qry qry[maxn];


void solve() {
    _rep(i, 1, m) {
        _rep(k, qry[i - 1].r + 1, qry[i].r) {
            if(vis[A[k]]) fwick.add(vis[A[k]], -1);
            
            vis[A[k]] = k;
            fwick.add(vis[A[k]], 1);
        }
        ANS[qry[i].id] = fwick.sum(qry[i].r) - fwick.sum(qry[i].l - 1);
        
        
    }
    
    _rep(i, 1, m) printf("%d\n", ANS[i]);
}

int main() {
    freopen("input.txt", "r", stdin);
    init();
    scanf("%d", &N);
    
    int maxv = 0;
    _rep(i, 1, N) {
        scanf("%d", &A[i]);
        maxv = max(maxv, A[i]);
    }
    
    fwick.resize(maxn);
    
    // == then input the query ==
    scanf("%d", &m);
    
    _rep(i, 1, m) {
        scanf("%d%d", &qry[i].l, &qry[i].r);
        qry[i].id = i;
    }
    
    sort(qry + 1, qry + 1 + m);
    
    // == then solve the problem ==
    solve();
}
