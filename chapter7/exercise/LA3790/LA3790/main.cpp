//
//  main.cpp
//  LA3790
//
//  Created by zhangmin chen on 2019/7/12.
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

const int R = 5;

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

int _hash(int r, int c) {
    return r * R + c;
}

void decode(const int x, int& r, int& c) {
    c = x % R;
    r = x / R;
}


class Grid {
public:
    int bitX, bitY;
    Grid(int _x = 0, int _y = 0) : bitX(_x), bitY(_y) {}
    
    inline void clear() {
        bitX = bitY = 0;
    }
    
    int getX(int r, int c) {
        return bitX & (1 << _hash(r, c));
    }
    int getY(int r, int c) {
        return bitY & (1 << _hash(r, c));
    }
    
    void setX(int r, int c) {
        bitX |= (1 << _hash(r, c));
    }
    void resetX(int r, int c) {
        bitX &= ~(1 << _hash(r, c));
    }
    void setY(int r, int c) {
        bitY |= (1 << _hash(r, c));
    }
    void resetY(int r, int c) {
        bitY &= ~(1 << _hash(r, c));
    }
    
    // usage: "_" setX(r, c)  OR  "|" setY(r, c)
    
    void fillGrid(int r, int c) {
        assert(0 <= r && r <= 2);
        // assert("green");
        
        setX(r, c); setY(r, c);
        
        setX(r, c+1); setX(r+2, c); setX(r+2, c+1);
        setY(r+1, c); setY(r, c+2); setY(r+1, c+2);
        
        resetX(r+1, c); resetX(r+1, c+1);
        resetY(r, c+1); resetY(r+1, c+1);
    }
    
    bool operator== (const Grid& rhs) const {
        return bitX == rhs.bitX && bitY == rhs.bitY;
    }
};

Grid target;

bool dfs(const Grid& grid, int d) {
    if(grid == target) return true;
    if(d >= 6) return false;
    
    _rep(r, 0, 2) _rep(c, 0, 2) {
        Grid nxt = grid;
        nxt.fillGrid(r, c);
        if(dfs(nxt, d+1)) return true;
    }
    return false;
}

void init() {
    //
    target.clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    
    string line;
    for(int kase = 1; ; kase++) {
        init();
        _for(i, 0, R) {
            getline(cin, line);
            if(line == "0") return 0;
            
            _for(j, 0, 9) {
                if(line[j] == ' ') continue;
                if(line[j] == '_') {
                    // (i, j/2) => bitX
                    target.setX(i, j/2);
                }
                if(line[j] == '|') {
                    // (i-1, j/2) => bitY
                    target.setY(i-1, j/2);
                }
            }
        }
        
        // finish input
        // then solve
        Grid st;
        bool ans = dfs(st, 0);
        
        printf("Case %d: ", kase);
        if(ans) printf("Yes\n");
        else printf("No\n");
        
    }
}

