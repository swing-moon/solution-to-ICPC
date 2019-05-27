//
//  main.cpp
//  DiceyProblem
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

const int maxn = 15;

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
    int face, back, top, bottom, left, right;
    Stat* prev;
    // why prev? did we need nxt?
    
    Stat() {
        prev = NULL;
    }
    
    Stat(int r, int c) : r(r), c(c) {}
    
    void init(int top, int face) {
        this->top = top;
        this->face = face;
        
        back = 7 - face;
        bottom = 7 - top;
        
        left = dice[face - 1][top - 1];
        right = 7 - left;
    }
    
    bool canMove(int dir);
    Stat* move(int dir);
    
    // usage: if(canMove(i)) move(i)
    
    int hash() const {
        return 1000 * (r-1) + 100 * (c-1) + 10 * top + face;
    }
};


typedef Stat* Statp;

class MemPool {
public:
    vector<Statp> buf;
    
    Statp create() {
        //
        buf.push_back(new Stat());
        return buf.back();
    }
    
    void fresh() {
        for(int i = 0; i < buf.size(); i++) delete buf[i];
        buf.clear();
    }
};

struct StatCmp {
    //
    bool operator() (const Statp& lhs, const Statp& rhs) const {
        return lhs->hash() < rhs->hash();
    }
};

MemPool pools;

bool Stat::canMove(int dir) {
    //
    int nr = r + dr[dir], nc = c + dc[dir];
    if(nr > R || nr < 1 || nc > C || nc < 1) return false;
    
    int mv = grid[nr][nc];
    if(mv == 0) return false;
    
    return mv == -1 || mv == top;
}

Statp Stat::move(int dir) {
    //
    // usage:
    // if(canMove(dir)) move(dir)
    Statp nxt = pools.create();
    int nr = r + dr[dir], nc = c + dc[dir];
    nxt->prev = this; nxt->r = nr; nxt->c = nc;
    
    if(dir == UP) nxt->init(face, bottom);
    if(dir == LEFT) nxt->init(right, face);
    if(dir == DOWN) nxt->init(back, top);
    if(dir == RIGHT) nxt->init(left, face);
    
    return nxt;
    
}

Statp bfs(const Stat& dest, Statp beg) {
    //
    queue<Statp> que;
    set<Statp, StatCmp> vis;
    
    que.push(beg);
    vis.insert(beg);
    
    while(!que.empty()) {
        Statp cur = que.front(); que.pop();
        if(cur->r == dest.r && cur->c == dest.c)
            return cur;
        
        for(int i = 0; i < 4; i++) {
            if(cur->canMove(i)) {
                Statp nxt = cur->move(i);
                
                if(vis.count(nxt)) continue;
                
                vis.insert(nxt);
                que.push(nxt);
            }
        }
    }
    return NULL;
}


int main() {
    freopen("input.txt", "r", stdin);
    string name;
    deque<Statp> res;
    
    while(cin >> name && name != "END") {
        memset(grid, 0, sizeof(grid));
        cin >> R >> C;
        int tmpR, tmpC, tmpT, tmpF;
        cin >> tmpR >> tmpC >> tmpT >> tmpF;
        
        Stat st(tmpR, tmpC);
        st.prev = NULL;
        st.init(tmpT, tmpF);
        
        for(int i = 1; i <= R; i++) for(int j = 1; j <= C; j++) cin >> grid[i][j];
        cout << name << endl;
        
        // finish init! then bfs()
        
        Statp ans = NULL;
        for(int i = 0; i < 4; i++) {
            if(st.canMove(i)) {
                ans = bfs(st, st.move(i));
                if(ans) break;
            }
        }
        
        if(ans) {
            res.clear();
            while(ans) {
                res.push_front(ans);
                ans = ans->prev;
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
