//
//  main.cpp
//  HDU1116-2
//
//  Created by zhangmin chen on 2019/5/22.
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
typedef set<string>::iterator ssii;

const int maxn = 256;
const int maxl = 2000 + 10;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

int deg[maxn], vis[maxn];
int pa[maxn];
int m, u, v;

void init() {
    Set(deg, 0);
    Set(vis, 0);
    Set(pa, 0);
}
void init_pa() {
    _rep(u, 'a', 'z') pa[u] = u;
}

int findset(int u) { return pa[u] != u ? pa[u] = findset(pa[u]) : u; }

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    cin >> kase;
    
    while(kase--) {
        init();
        init_pa();
        scanf("%d", &m);
        
        int cc = 26;
        char word[maxl];
        
        scanf("%d", &m);
        _for(i, 0, m) {
            scanf("%s", word);
            char u = word[0], v = word[strlen(word) - 1];
            
            deg[u]++;
            deg[v]--;
            vis[u] = vis[v] = 1;
            
            int s1 = findset(u), s2 = findset(v);
            if(s1 != s2) {
                pa[s1] = s2;
                cc--;
            }
        }
        
        
        vector<int> pNode;
        _rep(ch, 'a', 'z') {
            if(!vis[ch]) cc--;
            else if(deg[ch] != 0) pNode.push_back(deg[ch]);
        }
        
        bool exist = false;
        if(cc == 1 && ( (pNode.empty()) || (pNode.size() == 2 && (pNode[0] == 1 || pNode[0] == -1)) ) ) exist = true;
        
        if(exist) printf("Ordering is possible.\n");
        else printf("The door cannot be opened.\n");
    }
}

