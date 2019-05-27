//
//  main.cpp
//  LA3634
//
//  Created by zhangmin chen on 2019/4/21.
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


template <typename T>
class MemPool {
public:
    vector<T*> buf;
    
    T* create() {
        buf.push_back(new T());
        return buf.back();
    }
    
    void dispose() {
        for(int i = 0; i < buf.size(); i++) delete buf[i];
        buf.clear();
    }
};

map<set<int>, int> IDCache;
vector<set<int> > setCache;
MemPool<set<int> > pool;

void fresh() {
    IDCache.clear();
    setCache.clear();
}

int ID(const set<int>& st) {
    if(IDCache.count(st)) return IDCache[st];
    setCache.push_back(st);
    return IDCache[st] = (int)setCache.size() - 1;
}

// important

void solve() {
    stack<int> stk;
    int n;
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        string cmd;
        cin >> cmd;
        
        if(cmd[0] == 'P') {
            set<int> cur = *(pool.create());
            int pid = ID(cur);
            stk.push(pid);
        } else if (cmd[0] == 'D') {
            stk.push(stk.top());
        }
        else {
            set<int> st1 = setCache[stk.top()]; stk.pop();
            set<int> st2 = setCache[stk.top()]; stk.pop();
            set<int> combine;
            
            if(cmd[0] == 'U') set_union(st1.begin(), st1.end(), st2.begin(), st2.end(), inserter(combine, combine.begin()));
            if(cmd[0] == 'I') set_intersection(st1.begin(), st1.end(), st2.begin(), st2.end(), inserter(combine, combine.begin()));
            
            if(cmd[0] == 'A') {
                combine = st2;
                combine.insert(ID(st1));
            }
            
            stk.push(ID(combine));
        }
        cout << setCache[stk.top()].size() << endl;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    cin >> kase;
    while(kase--) {
        solve();
        printf("***\n");
        pool.dispose();
    }
}
