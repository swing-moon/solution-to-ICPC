#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <functional>
#include <cmath>
#define _for(i, a, b)   for(int i = (a); i < (b); i++)
#define _rep(i, a, b)   for(int i = (a); i <= (b); i++)


using namespace std;
const int maxn = 20+1;
const int maxm = 8;

struct Event {
    int time, id;
    bool type;
    bool operator< (const Event& e) const {
        return time > e.time;
    }

    Event(int t, int i, bool type = true):time(t), id(i), type(type) {}
};

struct Req{
    int tid, num, t0, t, dt;
};

struct Staf{
    int pid, k, s_evts[maxn], idx, last;
    bool operator< (const Staf& s) const {
        return last < s.last || (last == s.last && pid < s.pid);
    }
};

Req reqs[maxn];
Staf stafs[maxm];

int n,m,kase;
multiset<int> exeID;
set<int> stafID;
priority_queue<Event> evts;

struct StafCmp{
    bool operator() (int lhs, int rhs) const {
        return stafs[lhs] < stafs[rhs];
    }
};
set<int, StafCmp> handle[maxn];

void solve(){
    int time = evts.top().time;
    while(!evts.empty() && time == evts.top().time){
        const Event& e = evts.top();
        if(e.type)  exeID.insert(e.id);
        else    stafID.insert(e.id);

        evts.pop();
    }

    while(!exeID.empty() && !stafID.empty()){
        _for(i,0,n)     handle[i].clear();
        bool canAssign = false;

        for(auto& i : stafID){
            auto& si = stafs[i];
            _for(j,0,si.k){
                int eid = si.s_evts[j];

                if(!exeID.count(eid))
                    continue;

                canAssign = true;
                handle[eid].insert(si.idx);
                break;
            }
        }

        if(!canAssign) break;

        _for(i,0,n){
            auto& s_set = handle[i];
            while(exeID.count(i) && !s_set.empty()){
                exeID.erase(exeID.find(i));

                int si = *(s_set.begin());
                auto& s = stafs[si];

                s.last = time;
                evts.push(Event(time + reqs[i].t, s.idx, false));

                s_set.erase(si);    //only remove the first elements
                stafID.erase(s.idx);    // remove all elements whose id is s.idx
            }
        }
    }
    if(evts.empty()){
        cout<<"Scenario "<<kase++<<": All requests are serviced within "<<time<<" minutes."<<endl;
    }
}

int main(){
    map<int,int> cast;
    kase = 1;
    while(cin >> n && n){
        cast.clear();   exeID.clear();  stafID.clear();

        _for(i,0,n){
            auto& r = reqs[i];
            cin >> r.tid >> r.num >> r.t0 >> r.t >> r.dt;
            cast[r.tid] = i;
            r.tid = i;

            _for(j,0,r.num)
                evts.push(Event(r.t0 + r.dt*j, i));
        }

        cin >> m;
        _for(i,0,m){
            auto& s = stafs[i];
            cin >> s.pid >> s.k;
            _for(j,0,s.k){
                cin >> s.s_evts[j];
                s.s_evts[j] = cast[s.s_evts[j]];
            }

            s.last = 0;
            s.idx = i;
            evts.push(Event(0,s.idx,false));
        }

        while(!evts.empty())
            solve();
    }
}