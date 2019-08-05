//
//  main.cpp
//  UVA11995
//
//  Created by zhangmin chen on 2019/7/8.
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
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;


#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
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

queue<int> que;
priority_queue<int> pq;
stack<int> stk;

int n;

void init() {
    while(!que.empty()) que.pop();
    while(!pq.empty()) pq.pop();
    while(!stk.empty()) stk.pop();
}


int main() {
    freopen("input.txt", "r", stdin);
    
    while (scanf("%d", &n) != EOF) {
        init();
        int cmd, v;
        
        int tot = 0;
        int cntPQ = 0, cntS = 0, cntQ = 0;
        
        _for(i, 0, n) {
            scanf("%d%d", &cmd, &v);
            if(cmd == 1) {
                que.push(v);
                pq.push(v);
                stk.push(v);
            }
            else if(cmd == 2) {
                tot++;
                
                int xPQ = 0, xQ = 0, xS = 0;
                if(!que.empty()) {
                    xQ = que.front();
                    que.pop();
                }
                if(!pq.empty()) {
                    xPQ = pq.top();
                    pq.pop();
                }
                if(!stk.empty()) {
                    xS = stk.top();
                    stk.pop();
                }
                
                if(xQ == v) cntQ++;
                if(xS == v) cntS++;
                if(xPQ == v) cntPQ++;
            }
        }
        
        if( (cntPQ == tot && cntS == tot) || (cntPQ == tot && cntQ == tot) || (cntS == tot && cntQ == tot) )
            printf("not sure\n");
        else if(cntQ == tot)
            printf("queue\n");
        else if(cntS == tot)
            printf("stack\n");
        else if(cntPQ == tot)
            printf("priority queue\n");
        else
            printf("impossible\n");
    }
}
