//
//  main.cpp
//  BoxesLine
//
//  Created by zhangmin chen on 2019/4/18.
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

using namespace std;
typedef long long llong;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)

const int maxn = 100000 + 5;

class Node {
public:
    int data;
    Node *left, *right;
    
    Node() {
        data = 0;
        left = right = NULL;
    }
    bool operator== (const Node& rhs) const {
        return data == rhs.data;
    }
};

typedef Node* Nodep;

void link(Nodep l, Nodep r) {
    l->right = r;
    r->left = l;
}

Nodep nil;
Node box[maxn];

int N, M, OP;

void init(int n) {
    // box 0 is a nil
    
    nil = &(box[0]);
    nil->right = &(box[1]);
    nil->left = &(box[n]);
    for(int i = 1; i <= n; i++) {
        //
        Node& p = box[i];
        p.data = i;
        p.left = &(box[i-1]);
        p.right = &(box[(i+1) % (n+1)]);
    }
}

int main() {
    //
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int kase = 0;
    while(scanf("%d%d", &N, &M) == 2 && N) {
        //
        init(N);
        
        int x, y;
        int inv = 0;
    
        while(M--) {
            scanf("%d", &OP);
            
            if(OP == 4) {
                inv = 1 - inv;
            }
            else {
                if(inv && OP != 3) OP = 3 - OP;
                
                if(OP == 1) {
                    //
                    scanf("%d%d", &x, &y);
                    if(box[y].left->data == box[x].data) continue;
                    
                    link(box[x].left, box[x].right);
                    link(box[y].left, &box[x]);
                    link(&box[x], &box[y]);
                }
                else if(OP == 2) {
                    scanf("%d%d", &x, &y);
                    if(box[y].right->data == box[x].data) continue;
                    
                    link(box[x].left, box[x].right);
                    link(&box[x], box[y].right);
                    link(&box[y], &box[x]);
                }
                else if(OP == 3) {
                    scanf("%d%d", &x, &y);
                    if(box[y].right->data == box[x].data) {
                        //
                        link(&box[y], box[x].right);
                        link(box[y].left, &box[x]);
                        link(&box[x], &box[y]);
                    }
                    else if(box[x].right->data == box[y].data) {
                        //
                        link(&box[x], box[y].right);
                        link(box[x].left, &box[y]);
                        link(&box[y], &box[x]);
                    }
                    else {
                        //
                        Nodep yl = box[y].left;
                        Nodep yr = box[y].right;
                        
                        link(box[x].left, &box[y]);
                        link(&box[y], box[x].right);
                        link(yl, &box[x]);
                        link(&box[x], yr);
                    }
                }
            }
        }
        
        
        // finished!
        llong ans = 0;
        int cnt = 1;
        for(Nodep ptr = nil->right; ptr != nil; ptr = ptr->right, cnt++) {
            if(cnt % 2 == 1) ans += ptr->data;
        }
        
        if(inv && N % 2 == 0) ans = (llong) (N)*(N+1) / 2 - ans;
        printf("Case %d: %lld\n", ++kase, ans);
    }
}
