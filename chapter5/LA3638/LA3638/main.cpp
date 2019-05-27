//
//  main.cpp
//  LA3638
//
//  Created by zhangmin chen on 2019/5/18.
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



#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;



// we need to deal with the same priority
class Task {
public:
    int id, num;
    Task(int id_ = 0, int num_ = 0) : id(id_), num(num_) {}
};
queue<Task> tasks;
priority_queue<int> pq;

void init() {
    while(!tasks.empty()) tasks.pop();
    while(!pq.empty()) pq.pop();
}

int n, m;
int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    cin >> kase;
    
    while(kase--) {
        //
        init();
        cin >> n >> m;
        _for(i, 0, n) {
            int val;
            cin >> val;
            pq.push(val);
            tasks.push(Task(i, val));
        }
        
        int ans = 0;
        while(true) {
            if(pq.empty()) break;
            int v = pq.top();
            Task t = tasks.front();
            tasks.pop();
            
            if(t.num == v) {
                pq.pop();
                ans++;
                if(t.id == m) {
                    // cout << ans << endl;
                    break;
                }
            }
            else tasks.push(t);
        }
        
        cout << ans << endl;
    }
}
