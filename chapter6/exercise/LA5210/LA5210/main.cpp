//
//  main.cpp
//  LA5210
//
//  Created by zhangmin chen on 2019/4/17.
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

// dice[face][top] = left
// check:
// (1, 1) = null, (1, 2) = 3, (1, 3) = 5, (1, 4) = 2, (1, 5) = 4, (1, 6) = null
// (2, 1) = 4, (2, 2) = null, (2, 3) = 1, (2, 4) = 6, (2, 5) = null, (2, 6) = 3
// (3, 1) = 2, (3, 2) = 6, (3, 3) = null, (3, 4) = null, (3, 5) = 1, (3, 6) = 5
// (4, 1) = 5, (4, 2) = 1, (4, 3) = null, (4, 4) = null, (4, 5) = 6, (4, 6) = 2
// (5, 1) = 3, (5, 2) = null, (5, 3) = 6, (5, 4) = 1, (5, 5) = null, (5, 6) = 4
// (6, 1) = null, (6, 2) = 4, (6, 3) = 2, (6, 4) = 5, (6, 5) = 3, (6, 6) = null

const int maxn = 12;

const int dice[6][6] = {
    {-1, 3, 5, 2, 4, -1},
    {4, -1, 1, 6, -1, 3},
    {2, 6, -1, -1, 1, 5},
    {5, 1, -1, -1, 6, 2},
    {3, -1, 6, 1, -1, 4},
    {-1, 4, 2, 5, 3, -1}
};
const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = {0, -1, 0, 1};
// {up, left, down, right}

const int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3;

int R, C;
int grid[maxn][maxn];

class Stat {
public:
    int r, c;
    int face, top, left, back, bottom, right;
    Stat* prev;
    
    Stat(int r, int c) : r(r), c(c) {}
    Stat() {
        prev = NULL;
    }
    
    bool canMove(int dir);
    //
    Stat* move(int dir);
    
    void init(int face, int top) {
        this->face = face;
        this->top = top;
        
        back = 7 - face;
        bottom = 7 - top;
        left = dice[face-1][top-1];
        right = 7 - left;
    }
    int hash() const {
        return 1000 * (r-1) + 100 * (c-1) + 10 * face + top;
    }
    
};
typedef Stat* Statp;

struct StatpCMP {
    bool operator() (const Statp& lhs, const Statp& rhs) const {
        return lhs->hash() < rhs->hash();
    }
};

/*
template <typename T>
class MemPool {
public:
    vector<T*> buf;
    T* create() {
        buf.push_back(new T());
        return buf.back();
    }
    
    void fresh() {
        for(int i = 0; i < buf.size(); i++) delete buf[i];
        buf.clear();
    }
};
 */
class MemPool {
public:
    vector<Statp> buf;
    Statp create() {
        buf.push_back(new Stat());
        return buf.back();
    }
    void fresh() {
        for(int i = 0; i < buf.size(); i++) delete buf[i];
        buf.clear();
    }
};


MemPool pools;

bool Stat::canMove(int dir) {
    //
    int nr = r + dr[dir], nc = c + dc[dir];
    if(nr < 1 || nr > R || nc < 1 || nc > C) return false;
    
    int mv = grid[nr][nc];
    if(mv == 0) return false;
    return mv == -1 || mv == top;
}
// method: if(canMove(d)) move(d)

Statp Stat::move(int dir) {
    //
    
    // method: if(canMove(d)) move(d)
    Statp nxt = pools.create();
    int nr = r + dr[dir], nc = c + dc[dir];
    nxt->prev = this; nxt->r = nr; nxt->c = nc;
    
    //debug(nr);
    //debug(nc);
    //cout << endl;

    
    
    // then change the dice
    if(dir == UP) {
        nxt->init(bottom, face);
    }
    if(dir == LEFT) {
        nxt->init(face, right);
    }
    if(dir == DOWN) {
        nxt->init(top, back);
    }
    if(dir == RIGHT) {
        nxt->init(face, left);
    }
    return nxt;
}

Statp bfs(const Stat& dest, Statp beg) {
    set<Statp, StatpCMP> vis;
    queue<Statp> que;
    
    que.push(beg);
    vis.insert(beg);
    
    while(!que.empty()) {
        Statp cur = que.front(); que.pop();
        if(cur->r == dest.r && cur->c == dest.c) return cur;
        
        for(int d = 0; d < 4; d++) {
            if(!cur->canMove(d)) continue;
            Statp nxt = cur->move(d);
            //debug(vis.count(nxt));
            if(vis.count(nxt)) continue;
            
            vis.insert(nxt);
            que.push(nxt);
        }
    }
    return NULL;
}

int main() {
    freopen("input.txt", "r", stdin);
    string name;
    deque<Statp> res;
    
    while(cin >> name && name != "END") {
        cin >> R >> C;
        int tmpR, tmpC, tmpT, tmpF;
        cin >> tmpR >> tmpC >> tmpT >> tmpF;
        
        Stat st(tmpR, tmpC);
        st.init(tmpF, tmpT);
        st.prev = NULL;
        
        for(int i = 1; i <= R; i++) for(int j = 1; j <= C; j++) cin >> grid[i][j];
        cout << name << endl;
        
        // finished init, then bfs():
        Statp ans = NULL;
        for(int i = 0; i < 4; i++) {
            if(st.canMove(i)) {
                ans = bfs(st, st.move(i));
                //debug(ans.r);
                //debug(ans.c);
                //cout << endl;
                
                if(ans) break;
            }
        }
        
        //debug(ans->r), debug(ans->c);
        //cout << endl;
        
        if(ans) {
            //
            res.clear();
            while(ans) {
                res.push_front(ans);
                ans = ans->prev;
                //debug(ans->r);
                //debug(ans->c);
                //cout << endl;
            }
            
            for(int i = 0; i < res.size(); i++) {
                if(i) {
                    cout << ",";
                    if(i % 9 == 0) cout << endl;
                }
                
                if(i % 9 == 0) cout << "  ";
                cout << "(" << res[i]->r << "," << res[i]->c << ")";
            }
            cout << endl;
        }
        else
            cout << "  No Solution Possible" << endl;
        pools.fresh();
    }
}
