//
//  main.cpp
//  LA5222B
//
//  Created by zhangmin chen on 2019/5/10.
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

const int inf = 0x3f3f3f3f;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

class Topic {
public:
    int t;
    queue<int> table;
    
    Topic(int t_) {
        t = t_;
        while (!table.empty()) {
            table.pop();
        }
    }
    
    Topic() {
        t = 0;
        while (!table.empty()) {
            table.pop();
        }
    }
};

class Person {
public:
    int pid, k;
    vector<int> tids;
    int last, endT;
    
    bool operator< (const Person& rhs) const {
        if(last != rhs.last) return last < rhs.last;
        return pid < rhs.pid;
    }
};

int N, M;
map<int, Topic> topics;
vector<Person> persons;

void init() {
    topics.clear();
    persons.clear();
}

/*
 *
 int timing = min {all_t0}
 while(N) {
    int jump = inf;
    // update jump through nxt
    for(p = all persons)
        int nxt = inf
        update(nxt)
        jump = min(jump, nxt)
 
    timing = jump
 }
 
 */

void assign(Person& p, int& nxt, int& ans, int timing) {
    // default: p.endT < timing
    _for(i, 0, p.k) {
        // id = p.tids[i]
        Topic& tp = topics[p.tids[i]];
        if(tp.table.empty()) continue;
        
        // nxt = latest topic time
        nxt = min(nxt, tp.table.front());
        if(tp.table.front() <= timing) {
            // assign the topic
            nxt = timing + tp.t;
            ans = max(ans, nxt);
            p.last = timing;
            
            tp.table.pop();
            if(tp.table.empty()) N--;
            
            break;
        }
    }
    p.endT = nxt;
}


int main() {
    freopen("input.txt", "r", stdin);
    int kase = 1;
    
    while (cin >> N && N) {
        init();
        
        int timing = inf, ans = 0;
        _for(i, 0, N) {
            int tid, num, t0, t, dt;
            cin >> tid >> num >> t0 >> t >> dt;
            timing = min(timing, t0);
            
            Topic tp(t);
            
            while(num--) {
                //
                tp.table.push(t0);
                t0 += dt;
            }
            
            topics[tid] = tp;
        }
        
        cin >> M;
        persons.resize(M);
        _for(i, 0, M) {
            cin >> persons[i].pid >> persons[i].k;
            persons[i].tids.resize(persons[i].k);
            _for(j, 0, persons[i].k) {
                cin >> persons[i].tids[j];
            }
        }
        
        // we get all data
        
        while(N) {
            int jump = inf;
            sort(persons.begin(), persons.end());
            for(auto& p : persons) {
                int nxt = inf;
                // update(nxt), assigned the project
                // if can assign? else ?
                
                if(p.endT > timing) {
                    nxt = p.endT;
                }
                else {
                    assign(p, nxt, ans, timing);
                }
                
                jump = min(jump, nxt);
                // for p loop finished;
            }
            
            timing = jump;
            // while N loop finished
        }
        printf("Scenario %d: All requests are serviced within %d minutes.\n", kase++, ans);
    }
}
