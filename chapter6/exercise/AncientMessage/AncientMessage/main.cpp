//
//  main.cpp
//  AncientMessage
//
//  Created by zhangmin chen on 2019/4/19.
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

const int maxh = 200 + 5;
const int maxw = 50 * 4 + 5;

int H, W;
// H += 2, W = W * 4 + 2;

char h2b[256][5];
int data[maxh][maxw], ccid[maxh][maxw];
char origin[maxh][maxw];

void init() {
    strcpy(h2b['0'], "0000");
    strcpy(h2b['1'], "0001");
    strcpy(h2b['2'], "0010");
    strcpy(h2b['3'], "0011");
    strcpy(h2b['4'], "0100");
    strcpy(h2b['5'], "0101");
    strcpy(h2b['6'], "0110");
    strcpy(h2b['7'], "0111");
    strcpy(h2b['8'], "1000");
    strcpy(h2b['9'], "1001");
    strcpy(h2b['a'], "1010");
    strcpy(h2b['b'], "1011");
    strcpy(h2b['c'], "1100");
    strcpy(h2b['d'], "1101");
    strcpy(h2b['e'], "1110");
    strcpy(h2b['f'], "1111");
}


void readData(const char h2b[][5], int maxr, int maxc) {
    // for i = 0 to row
    // char ch = origin[row][col]

    memset(data, 0, sizeof(data));
    //memset(origin, 0, sizeof(origin));
    memset(ccid, 0, sizeof(ccid));
    
    for(int r = 0; r < maxr; r++) for(int c = 0; c < maxc; c++) {
        char ch = origin[r][c];
        //debug(ch);
        
        // get h2b[ch][i]-'0'
        
        for(int i = 0; i < 4; i++) {
            // data restore value data[1..H][1..W]
            data[r+1][c * 4 + i + 1] = h2b[ch][i] - '0';
            //debug(h2b[ch][i] - '0');
        }
    }
    
    H += 2;
    W = W * 4 + 2;
    
    // Now data row [0, H)
    // col [0, W)
    
}

const char* code = "WAKJSD";
// count connected components

// 1 is the background ccid
// Message ccid start from [2...)
// main: cnt = 0 dfs(++cnt);
// ccid = 0, means have not visited!

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, -1, 0, 1};

bool valid(int r, int c) {
    if(r >= 0 && r < H && c >= 0 && c < W) return true;
    else return false;
}

void dfs(int r, int c, int cnt) {
    ccid[r][c] = cnt;
    for(int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        
        if(valid(nr, nc) && ccid[nr][nc] == 0 && data[nr][nc] == data[r][c])
            dfs(nr, nc, cnt);
    }
}

// then solve()
// cnt = 0  -> if ccid == 0  dfs(++cnt)
// we solve black position, which is msg
// we can't get the specified words directely, but we have ccid
// regard ccid as words identity

vector<int> msg;
int msgID() {
    int cnt = 0;
    for(int i = 0; i < H; i++) for(int j = 0; j < W; j++) {
        if(ccid[i][j] != 0) continue;
        
        dfs(i, j, ++cnt);
        if(data[i][j] == 1) msg.push_back(cnt);
    }
    return cnt;
}

// for i = msg to msg.size()
// msg[i] is the id of words, words[ccid[r][c]] point to the specified words
// recogonize(msg[i])


vector<set<int> > words;
// if it is a msg position, then cntHole()
void cntHole(int r, int c) {
    for(int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        
        if(valid(nr, nc) && data[nr][nc] == 0 && ccid[nr][nc] != 1) {
            //
            words[ccid[r][c]].insert(ccid[nr][nc]);
        }
    }
}

void decode() {
    int cnt = msgID();
    //debug(cnt);
    words.clear();
    words.resize(cnt+1);
    
    for(int i = 0; i < H; i++) for(int j = 0; j < W; j++) {
        if(data[i][j] == 1) cntHole(i, j);
    }
}

char recognize(int id) {
    int cnt = (int)words[id].size();
    return code[cnt];
}
// usage: for i = 0 to msg.size
// int curid = msg[i]
// recognize(curid)


void fresh() {
    msg.clear();
    words.clear();
    memset(origin, 0, sizeof(origin));
}

int main() {
    freopen("input.txt", "r", stdin);
    init();
    
    int kase = 0;
    while(scanf("%d%d", &H, &W) && H) {
        for(int i = 0; i < H; i++)
            scanf("%s", origin[i]);
        
        readData(h2b, H, W);
        // then we finished init();
        
        /*
        for(int i = 0; i < H; i++) {
            for(int j = 0; j < W; j++) cout << data[i][j];
            cout << endl;
        }
         */
        
        // try to solve()
        decode();
        
        vector<char> ans;
        for(int i = 0; i < msg.size(); i++) {
            int curid = msg[i];
            ans.push_back(recognize(curid));
            //debug(ans.size());
        }
        sort(ans.begin(), ans.end());
        
    
        
        
        printf("Case %d: ", ++kase);
        // print out Message
        for(int i = 0; i < ans.size(); i++) printf("%c", ans[i]);
        puts("");
        fresh();
        ans.clear();
    }
    
}
