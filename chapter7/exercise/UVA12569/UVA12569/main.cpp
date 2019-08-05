//
//  main.cpp
//  UVA12569
//
//  Created by zhangmin chen on 2019/7/25.
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
#include <bitset>
#include <assert.h>

using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;

const int maxn = 15 + 5;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(a))
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

int read() {
    int x;
    scanf("%d", &x);
    return x;
}

template <typename T>
class Mempool {
public:
    vector<T*> buf;
    T* create() {
        buf.push_back(new T());
        return buf.back();
    }
    
    void reset() {
        _for(i, 0, buf.size()) delete buf[i];
        buf.clear();
    }
};

class Node {
public:
    int from, to;
    Node* nxt;
};

class State {
public:
    Node* path;
    int st, dist;
    State(int s = 0, int d = 0, Node* p = NULL) : st(s), dist(d), path(p) {}
    
    inline void setOBS(int u) {
        st |= (1 << (4 + u));
    }
    inline void resetOBS(int u) {
        st &= ~(1 << (4 + u));
    }
    
    inline bool existOB(int u) const {
        return st & (1 << (4 + u));
    }
    
    inline void setROB(int ru) {
        st = ((st >> 4) << 4) | ru;
    }
    inline int getROB() const {
        //
        return st & 0xf;
    }
};



Mempool<Node> pools;

Node* newNode(Node* nxt = NULL, int from = -1, int to = -1) {
    Node* p = pools.create();
    p->nxt = nxt;
    p->from = from;
    p->to = to;
    return p;
}

vector<int> G[maxn];
int vis[1 << 19];
int obs[maxn];
queue<State> que;

int N, M, S, T;

void init() {
    _for(i, 0, maxn) G[i].clear();
    Set(vis, 0);
    Set(obs, 0);
    
    while(!que.empty()) que.pop();
}

void initBFS() {
    //
    State beg;
    _for(i, 0, M) beg.setOBS(obs[i]);
    beg.setROB(S);
    
    que.push(beg);
    // debug(beg.st);
    vis[beg.st] = 1;
}

void Move(const State& St, int u, queue<State>& que) {
    // Move from u -> v
    
    int RPOS = St.getROB();
    
    _for(i, 0, G[u].size()) {
        //
        int v = G[u][i];
        State cur = St;
        if(v == RPOS || cur.existOB(v)) continue;
        
        if(u == RPOS) {
            //
            cur.st = ((St.st >> 4) << 4) | v;
            // debug(cur.st);
        }
        else {
            //
            cur.st ^= (1 << (4 + u));
            cur.st |= (1 << (4 + v));
        }
        
        if(vis[cur.st]) continue;
        vis[cur.st] = 1;
        State nxt(cur.st, St.dist + 1, newNode(St.path, u, v));
        que.push(nxt);
    }
}

ostream& operator<< (ostream& os, Node* p) {
    if(p == NULL) return os;
    os << p->nxt << p->from + 1 << " " << p->to + 1 << endl;
    return os;
}

void BFS() {
    //
    initBFS();
    while (!que.empty()) {
        const State x = que.front();
        // debug(x.getROB());
        // debug(T);
        que.pop();
        
        if(x.getROB() == T) {
            printf("%d\n", x.dist);
            cout << x.path;
            return;
        }
        
        Move(x, x.getROB(), que);
        _for(i, 0, N) if(x.existOB(i)) Move(x, i, que);
    }
    cout << "-1" << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase = read();
    
    _rep(t, 1, kase) {
        init();
        scanf("%d%d%d%d", &N, &M, &S, &T);
        S--; T--;
        
        printf("Case %d: ", t);
        
        _for(i, 0, M) obs[i] = read() - 1;
        
        _for(i, 0, N - 1) {
            int u = read() - 1, v = read() - 1;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        
        // then we finished input
        // initBFS and BFS
        BFS();
        pools.reset();
        cout << endl;
    }
}
