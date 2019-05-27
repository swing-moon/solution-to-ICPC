//
//  main.cpp
//  HDU3726
//
//  Created by zhangmin chen on 2019/3/2.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

struct Node {
    Node* cld[2];
    int rk;
    int val;
    int sz;
    
    Node(int v) : val(v) {
        cld[0] = cld[1] = NULL;
        rk = rand();
        sz = 1;
    }
    
    int cmp(int x) const {
        if(x == val) return -1;
        return x < val ? 0 : 1;
    }
    
    void maintain() {
        sz = 1;
        if(cld[0] != NULL) sz += cld[0]->sz;
        if(cld[1] != NULL) sz += cld[1]->sz;
    }
};

typedef Node* Nodep;
typedef long long llong;

void rotate(Nodep &o, int d) {
    Nodep k = o->cld[d^1];
    o->cld[d^1] = k->cld[d];
    k->cld[d] = o;
    
    o->maintain();
    k->maintain();
    o = k;
}

void insert(Nodep &o, int x) {
    if(o == NULL) o = new Node(x);
    else {
        //
        int d = (x < o->val ? 0 : 1);
        insert(o->cld[d], x);
        
        if(o->cld[d]->rk > o->rk) rotate(o, d^1);
    }
    o->maintain();
}

void remove(Nodep &o, int x) {
    //
    int d = o->cmp(x);
    if(d == -1) {
        // exist
        Nodep u = o;
        if(o->cld[0] != NULL && o->cld[1] != NULL) {
            //
            int d2 = (o->cld[0]->rk > o->cld[1]->rk ? 1 : 0);
            rotate(o, d2);
            remove(o->cld[d2], x);
        } else {
            if(o->cld[0] == NULL) o = o->cld[1];
            else o = o->cld[0];
            delete u;
        }
        
    } else {
        remove(o->cld[d], x);
    }
    if(o != NULL) o->maintain();
}


const int maxn = 20000 + 10;
const int maxm = 60000 + 10;
const int maxc = 500000 + 10;

struct Edge {
    int from, to;
};
Edge edges[maxm];
int weight[maxn], rmved[maxm];

int pa[maxn];
void init_pa() {
    for(int i = 0; i < maxn; i++) pa[i] = i;
}

int findset(int x) { return pa[x] != x ? pa[x] = findset(pa[x]) : x; }

Nodep root[maxn];

struct CMD {
    char type;
    int x, p;
}cmds[maxc];

int kth(Nodep o, int k) {
    if(o == NULL || k <= 0 || k > o->sz) return 0;
    int s = (o->cld[1] == NULL ? 0 : o->cld[1]->sz);
    if(k == s+1) return o->val;
    else if(k <= s) return kth(o->cld[1], k);
    else return kth(o->cld[0], k-s-1);
}

void mergeto(Nodep &src, Nodep &dest) {
    if(src->cld[0] != NULL) mergeto(src->cld[0], dest);
    if(src->cld[1] != NULL) mergeto(src->cld[1], dest);
    
    insert(dest, src->val);
    delete src;
    src = NULL;
}

void rmvTree(Nodep &x) {
    if(x->cld[0] != NULL) rmvTree(x->cld[0]);
    if(x->cld[1] != NULL) rmvTree(x->cld[1]);
    delete x;
    x = NULL;
}

void addEdge(int x) {
    int u = findset(edges[x].from), v = findset(edges[x].to);
    if(u != v) {
        // not in the same scc
        if(root[u]->sz < root[v]->sz) {
            pa[u] = v;
            mergeto(root[u], root[v]);
        } else {
            pa[v] = u;
            mergeto(root[v], root[u]);
        }
    }
}


void changeW(int x, int v) {
    int u = findset(x);
    remove(root[u], weight[x]);
    insert(root[u], v);
    weight[x] = v;
}

int qCnt = 0;
llong ans = 0;

void query(int x, int k) {
    qCnt++;
    ans += kth(root[findset(x)], k);
}

int n, m;
int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;
    while(scanf("%d%d", &n, &m) == 2 && n) {
        for(int i = 1; i <= n; i++) scanf("%d", &weight[i]);
        for(int i = 1; i <= m; i++) scanf("%d%d", &edges[i].from, &edges[i].to);
        memset(rmved, 0, sizeof(rmved));
        
        int cnt = 0;
        for(;;) {
            char type;
            int x, p = 0, v = 0;
            cin >> type;
            if(type == 'E') break;
            
            scanf("%d", &x);
            if(type == 'D') rmved[x] = 1;
            if(type == 'Q') scanf("%d", &p);
            if(type == 'C') {
                scanf("%d", &v);
                p = weight[x];
                weight[x] = v;
            }
            cmds[cnt++] = (CMD) { type, x, p };
        }
        // finish cmd
        
        for(int i = 1; i <= n; i++) {
            pa[i] = i;
            if(root[i] != NULL) rmvTree(root[i]);
            root[i] = new Node(weight[i]);
        }
        
        for(int i = 1; i <= m; i++) if(!rmved[i]) addEdge(i);
        
        ans = qCnt = 0;
        for(int i = cnt-1; i >= 0; i--) {
            if(cmds[i].type == 'D') addEdge(cmds[i].x);
            if(cmds[i].type == 'Q') query(cmds[i].x, cmds[i].p);
            if(cmds[i].type == 'C') changeW(cmds[i].x, cmds[i].p);
        }
        
        printf("Case %d: %.6lf\n", ++kase, ans / (double)qCnt);
    }
}

