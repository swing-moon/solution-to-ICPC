//
//  main.cpp
//  LA5147
//
//  Created by zhangmin chen on 2019/7/7.
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

const int maxn = 20 + 5;


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

int pa[maxn];
set<int> G[maxn];
int n, k;

// Graph start from 1

void init() {
    //
    Set(pa, 0);
    _for(i, 0, maxn) G[i].clear();
}

void initSet() {
    _for(i, 0, maxn) pa[i] = i;
}

int findSet(int x) {
    return pa[x] == x ? x : (pa[x] = findSet(pa[x]));
}

// regard path as status in IDA*
// expand path

ostream& operator<< (ostream& os, const vector<int>& path) {
    bool first = true;
    _for(i, 0, path.size()) {
        if(first) first = false;
        else os << ' ';
        os << path[i];
    }
    return os;
}

void dfs(int u, int dest, vector<int>& path, vector<string>& paths) {
    path.push_back(u);
    
    if(u == dest) {
        stringstream ss;
        ss << path;
        paths.push_back(ss.str());
    }
    
    _forS(i, G[u].begin(), G[u].end()) {
        int v = *i;
        if(find(path.begin(), path.end(), v) != path.end()) continue;
        dfs(v, dest, path, paths);
    }
    
    path.pop_back();
}

int main() {
    //
    freopen("input.txt", "r", stdin);
    for(int kase = 1, from, to; scanf("%d", &k) == 1 && k; kase++) {
        init();
        initSet();
        while(true) {
            scanf("%d%d", &from, &to);
            if(from == 0 || to == 0) break;
            G[from].insert(to);
            G[to].insert(from);
            
            int p1 = findSet(from);
            int p2 = findSet(to);
            if(p1 != p2) pa[p1] = p2;
        }
        
        // finish build graph
        // then solve()
        
        vector<int> path;
        vector<string> paths;
        if(findSet(pa[1]) == findSet(pa[k])) dfs(1, k, path, paths);
        
        printf("CASE %d:\n", kase);
        _for(i, 0, paths.size()) cout << paths[i] << endl;
        printf("There are %lu routes from the firestation to streetcorner %d.\n", paths.size(), k);
    }
}
