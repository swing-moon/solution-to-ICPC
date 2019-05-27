//
//  main.cpp
//  UVA804
//
//  Created by zhangmin chen on 2019/3/6.
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

using namespace std;
typedef long long llong;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define REP(i, l, r) for(int i = (l); i <= (r); i++)
#define FOR(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)

typedef vector<int>::iterator VI;
typedef map<int, int>::iterator MI;

int read() {
    int x; scanf("%d", &x); return x;
}

vector<int> places;

struct Trans {
    vector<int> to;
    map<int, int> from;
    
    void init() {
        to.clear();
        from.clear();
    }
    
    bool valid() {
        for(MI p = from.begin(); p != from.end(); p++) {
            //
            if(places[p->first] < p->second) return false;
        }
        return true;
    }
    
    void op() {
        for(MI p = from.begin(); p != from.end(); p++) {
            // if valid
            places[p->first] -= p->second;
        }
        
        for(int i = 0; i < to.size(); i++) {
            int id = to[i];
            places[id]++;
        }
    }
};

vector<Trans> trans;
typedef vector<Trans>::iterator TI;

void dbg(Trans& tr) {
    for(int i = 0; i < tr.to.size(); i++) debug_(tr.to, i);

    for(MI p = tr.from.begin(); p != tr.from.end(); p++) {
        debug_m(tr.from, p);
    }
    
    cout << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int np;
    for(int kase = 1; cin >> np && np; kase++) {
        //
        places.clear();
        trans.clear();
        
        for(int i = 0; i < np; i++) {
            int x = read();
            places.push_back(x);
        }
        
        int nt;
        nt = read();
        
        for(int i = 0; i < nt; i++) {
            int x;
            Trans ti;
            ti.init();
            
            while(scanf("%d", &x) && x) {
                if(x < 0) ti.from[-x-1]++;
                else ti.to.push_back(x-1);
            }
            
            trans.push_back(ti);
        }
        
        // simulate
        int nf;
        nf = read();
        
        int cnt = 0;
        bool live = true;
        for(int i = 0; i < nf; i++) {
            
            int k;
            for(k = 0; k < trans.size(); k++) {
                if(trans[k].valid()) break;
            }
            // choose trans[k]
            if(k == trans.size()) live = false;
            if(!live) break;
            
            Trans& cur = trans[k];
            cur.op();
            
            // debug
            //cout << "dbg cnt: " << cnt << endl;
            //dbg(cur);
            
            cnt++;
        }
        
        //for(int i = 0; i < trans.size(); i++) dbg(trans[i]);
        
        // print_out
        printf("Case %d:", kase);
        if(live) printf(" still live after %d transitions\n", cnt);
        else printf(" dead after %d transitions\n", cnt);
        
        printf("Places with tokens:");
        for(int i = 0; i < places.size(); i++) {
            int val = places[i];
            if(val) printf(" %d (%d)", i+1, val);
        }
        printf("\n");
        printf("\n");
    }
}
