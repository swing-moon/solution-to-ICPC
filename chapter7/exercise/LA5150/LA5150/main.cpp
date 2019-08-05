//
//  main.cpp
//  LA5150
//
//  Created by zhangmin chen on 2019/7/11.
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
typedef set<int>::iterator ssii;

const int COL = 8;
const int ROW = 7;
const int dx[] = {0, 1};
const int dy[] = {1, 0};
const int maxn = 28;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
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

class Pips {
public:
    int x, y;
    Pips(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

int grid[ROW][COL], ans[ROW][COL];

int getCard[ROW][ROW];
Pips cards[maxn];

// cards <-> getCard[][]
// usage: cards[getCard[i][j]]
// ID = getCard[i][j]


void init() {
    Set(grid, 0);
    Set(ans, -1);
    Set(cards, 0);
    Set(getCard, -1);
}

int read() {
    int x;
    scanf("%d", &x);
    return x;
}

void initCards() {
    int cnt = 0;
    
    _for(i, 0, ROW) _for(j, i, ROW) {
        Pips& cur = cards[cnt];
        
        cur.x = i; cur.y = j;
        getCard[i][j] = cnt;
        
        cnt++;
    }
}

int getBone(int x, int y) {
    if(x > y) return getBone(y, x);
    return getCard[x][y];
}

bool nxt(Pips& pos) {
    int pr = pos.x, pc = pos.y;
    pc++;
    
    pr += pc / COL;
    pc %= COL;
    
    if(pr >= ROW) return false;
    pos.x = pr; pos.y = pc;
    
    return true;
}

bool inRange(int x, int left, int right) {
    if(left >= right) return inRange(x, right, left);
    return left <= x && x <= right;
}

bool valid(int r, int c) {
    return inRange(r, 0, ROW - 1) && inRange(c, 0, COL - 1);
}

void dfs(const Pips& pos, set<int> cardID, int& cnt) {
    if(cardID.size() == maxn) {
        cnt++;
        _for(i, 0, ROW) {
            printf(" ");
            _for(j, 0, COL) printf("%4d", ans[i][j] + 1);
            printf("\n");
        }
        printf("\n");
        return;
    }
    
    // then cut stretch
    // if cur position is been assigned
    // dfs from _nxt
    Pips _nxt = pos;
    if(ans[_nxt.x][_nxt.y] != -1) {
        if(nxt(_nxt)) dfs(_nxt, cardID, cnt);
        return;
    }
    
    // then assign the card
    _nxt = pos;
    if(!nxt(_nxt)) return;
    
    _for(dir, 0, 2) {
        int px = pos.x, py  = pos.y;
        int nx = px + dx[dir], ny = py + dy[dir];
        
        if(!valid(nx, ny)) continue;
        if(ans[nx][ny] != -1) continue;
        
        int _bone = getBone(grid[px][py], grid[nx][ny]);
        if(_bone != -1 && !cardID.count(_bone)) {
            Pips _nxt = pos; nxt(_nxt);
            
            ans[px][py] = ans[nx][ny] = _bone;
            cardID.insert(_bone);
            dfs(_nxt, cardID, cnt);
            cardID.erase(_bone);
            ans[px][py] = ans[nx][ny] = -1;
        }
    }
}



int main() {
    freopen("input.txt", "r", stdin);
    init();
    initCards();
    
    int kase = 1;
    while (true) {
        Pips st(0, 0);
        if(scanf("%d", &grid[st.x][st.y]) != 1) break;
        while(nxt(st)) grid[st.x][st.y] = read();
        
        // finish input
        // then solve()
        
        if(kase > 1) printf("\n\n\n");
        printf("Layout #%d:\n\n", kase);
        _for(i, 0, ROW) {
            _for(j, 0, COL) printf("%4d", grid[i][j]);
            printf("\n");
        }
        printf("\nMaps resulting from layout #%d are:\n\n", kase);
        
        
        int cnt = 0;
        set<int> cardID;
        dfs(Pips(), cardID, cnt);
        
        printf("There are %d solution(s) for layout #%d.\n", cnt, kase);
        
        kase++;
        init();
        initCards();
    }
    
}
