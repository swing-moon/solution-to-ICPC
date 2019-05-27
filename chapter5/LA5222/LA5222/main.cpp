//
//  main.cpp
//  LA5222
//
//  Created by zhangmin chen on 2019/5/8.
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

const int MAXTIME = 500000;

class Topic {
public:
    int tid, num, t0, t, dt;
    int tot;
};

class Cust {
public:
    int pid, k;
    vector<int> cTopics;
    
    int dtime, handle, last;
    bool busy;
    
    Cust() {
        pid = -1;
        k = 0;
        cTopics.clear();
        
        dtime = 0;
        handle = -1;
        last = 0;
        busy = 0;
    }
    
    bool operator< (const Cust& rhs) const {
        if(last == rhs.last) return pid > rhs.pid;
        return last > rhs.last;
    }
};

vector<Topic> topics;
vector<Cust> custs;

map<int, int> idxT;
map<int, int> idxC;

map<int, vector<Cust> > buf;
typedef map<int, vector<Cust> >::iterator mv;

bool can_assign(int tID, int timing) {
    //
    if(timing < topics[tID].t0) return 0;
    if(topics[tID].dt == 0) return topics[tID].num > 0;
    if(topics[tID].num == 0) return 0;
    
    int arriving = (timing - topics[tID].t0) / topics[tID].dt;
    int already_assigned = topics[tID].tot - topics[tID].num;
    
    if(arriving < already_assigned) return 0;
    return 1;
}

void init() {
    topics.clear();
    custs.clear();
    idxT.clear();
    idxC.clear();
    buf.clear();
}


int main() {
    freopen("input.txt", "r", stdin);
    int n, m, kase = 0;
    
    // n topics, m custs
    while(cin >> n && n) {
        init();
        int timing = 0;
        
        for(int i = 0; i < n; i++) {
            Topic tp;
            cin >> tp.tid >> tp.num >> tp.t0 >> tp.t >> tp.dt;
            
            tp.tot = tp.num;
            idxT[tp.tid] = i;
            
            topics.push_back(tp);
        }
        
        cin >> m;
        for(int i = 0; i < m; i++) {
            Cust cst;
            cin >> cst.pid >> cst.k;
            idxC[cst.pid] = i;
            
            for(int j = 0; j < cst.k; j++) {
                int x;
                cin >> x;
                cst.cTopics.push_back(idxT[x]);
            }
            
            custs.push_back(cst);
        }
        // finished input data
        
        for(timing = 0; timing < MAXTIME; timing++) {
            buf.clear();
            // check busy of each custs
            for(int i = 0; i < m; i++) {
                if(!custs[i].busy) {
                    for(int j = 0; j < custs[i].k; j++) {
                        int tp = custs[i].cTopics[j];
                        if(can_assign(tp, timing)) {
                            // assign tp to custs[i]
                            if(!buf.count(tp)) buf[tp] = vector<Cust> ();
                            buf[tp].push_back(custs[i]);
                            break;
                        }
                    }
                }
            }
            
            // check buf
            for(mv it = buf.begin(); it != buf.end(); it++) {
                sort(it->second.begin(), it->second.end());
                int c = idxC[it->second[0].pid];
                custs[c].busy = 1;
                custs[c].last = timing;
                custs[c].handle = it->first;
                topics[it->first].num--;
            }
            
            // update custs dtime
            for(int i = 0; i < m; i++) {
                if(custs[i].busy) custs[i].dtime++;
                int tp = custs[i].handle;
                
                if(custs[i].busy && custs[i].dtime == topics[tp].t) {
                    custs[i].busy = 0;
                    custs[i].dtime = 0;
                }
            }
            
            // check finished
            int finished = 1;
            
            for(int i = 0; i < n; i++) {
                if(topics[i].num > 0) {
                    finished = 0;
                    break;
                }
            }
            
            for(int i = 0; i < m; i++) {
                if(custs[i].busy > 0) {
                    finished = 0;
                    break;
                }
            }
            
            
            if(finished) break;
            // timing loop finished!
        }
        
        
        printf("Scenario %d: All requests are serviced within %d minutes.\n", ++kase, timing + 1);
        // while finished!
    }
}
