//
//  main.cpp
//  queue-and-a2
//
//  Created by zhangmin chen on 2018/8/21.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

const int Maxtime = 500000;
using namespace std;

struct Topic {
    int tid, num, t0, t, dt;
    int start_n;
};

struct Member {
    int pid, k, last, category, busy;
    int dtime;
    vector<int> pidk;
    bool operator < (const Member& a) const {
        if(a.last == last)  return a.pid > pid;
        else    return a.last > last;
    }
    void init() {
        dtime = busy = last = 0;
    }
};

vector<Topic> topics;
vector<Member> staffs;
map<int, int> idx_t;
map<int, int> idx_m;
map<int, vector<Member> > ass;
//assign topics

//we get assigned id, if (timing-topics[tx].t0) / topics[tx].dt == (topics[tx].start_n - topics[tx].num)
// it means correspounding topics has been assigned
int can_exe(int tx, int t) {
    if(t < topics[tx].t0)   return 0;
    if(topics[tx].dt == 0)  return topics[tx].num > 0;
    if(topics[tx].num == 0) return 0;
    if((t-topics[tx].t0) / topics[tx].dt == (topics[tx].start_n - topics[tx].num -1))
        return 0;
    return 1;
}

int main() {
    int m, n, kase = 0;
    // m for topics, n for staffs
    
    while(cin >> m && m) {
        int timing = 0;
        topics.clear();
        staffs.clear();
        idx_m.clear();
        idx_t.clear();
        
        for(int i = 0; i < m; i++) {
            Topic xt;
            cin >> xt.tid >> xt.num >> xt.t0 >> xt.t >> xt.dt;
            xt.start_n = xt.num;
            topics.push_back(xt);
            idx_t[xt.tid] = i;
        }
        cin >> n;
        for(int i = 0; i < n; i++) {
            Member xm;
            xm.pidk.clear();
            // init!
            xm.dtime = xm.busy = xm.last = 0;
            int x;
            cin >> xm.pid >> xm.k;
            idx_m[xm.pid] = i;
            for(int j = 0; j < xm.k; j++) {
                cin >> x;
                xm.pidk.push_back(x);
            }
            staffs.push_back(xm);
        }
        
        //loop:
        for(timing = 0; timing < Maxtime; timing++) {
            ass.clear();
            for(int i = 0; i < n; i++) {
                // find free member
                if(!staffs[i].busy) {
                    for(int j = 0; j < staffs[i].k; j++) {
                        int choice = idx_t[staffs[i].pidk[j]];
                        //I got a bug in this!
                        if(can_exe(choice, timing)) {
                            if(!ass.count(choice))  ass[choice] = vector<Member> ();
                            ass[choice].push_back(staffs[i]);
                            break;
                            // a member only can be assigned one topic!
                        }
                    }
                }
            }
            
            //choose the best person!
            // it->first assigned to best member in it->second!
            map<int, vector<Member> >::iterator it;
            for(it = ass.begin(); it != ass.end(); it++) {
                sort(it->second.begin(), it->second.end());
                int cur_t = idx_m[it->second[0].pid];
                staffs[cur_t].busy = 1;
                staffs[cur_t].last = timing;
                staffs[cur_t].category = it->first;
                topics[it->first].num--;
            }
            
            int finished = 1;
            for(int i = 0; i < n; i++) {
                if(staffs[i].busy)  staffs[i].dtime++;
                int handle = staffs[i].category;
                if(staffs[i].busy && staffs[i].dtime == topics[handle].t) {
                    staffs[i].busy = 0;
                    staffs[i].dtime = 0;
                }
            }
            
            for(int i = 0; i < m; i++)  {
                if(topics[i].num > 0) {
                    finished = 0;   break;
                }
            }
            for(int i = 0; i < n; i++) {
                if(staffs[i].dtime > 0) {
                    finished = 0;   break;
                }
            }
            
            if(finished)    break;
        }
        
        printf("Scenario %d: All requests are serviced within %d minutes.\n",++kase, timing+1);
    }
}

