//
//  main.cpp
//  coloredCubes
//
//  Created by zhangmin chen on 2019/4/11.
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


/*
int Left[6] = {4, 0, 2, 3, 5, 1};
int Up[6] = {2, 1, 5, 0, 4, 3};

void rot(int* trans, int* pos) {
    int q[6];
    memcpy(q, pos, sizeof(q));
    for(int i = 0; i < 6; i++) {
        pos[i] = trans[q[i]];
    }
}

void enumerate() {
    int p0[6] = {0, 1, 2, 3, 4, 5};
    printf("dice24[24][6]: \n");
    
    for(int i = 0; i < 6; i++) {
        int q[6];
        memcpy(q, p0, sizeof(q));
        
        if(i == 0) rot(Up, q);
        if(i == 1) {
            rot(Left, q); rot(Up, q);
        }
        if(i == 3) {
            rot(Up, q); rot(Up, q);
        }
        if(i == 4) {
            rot(Left, q); rot(Left, q); rot(Left, q); rot(Up, q);
        }
        if(i == 5) {
            rot(Left, q); rot(Left, q); rot(Up, q);
        }
        
        for(int k = 0; k < 4; k++) {
            printf("{%d, %d, %d, %d, %d, %d},\n", q[0], q[1], q[2], q[3], q[4], q[5]);
            rot(Left, q);
        }
    }
    cout << endl;
}

int main() {
    enumerate();
}
 */

/*
 *
 dice24[24][6]:
 {2, 1, 5, 0, 4, 3},
 {2, 0, 1, 4, 5, 3},
 {2, 4, 0, 5, 1, 3},
 {2, 5, 4, 1, 0, 3},
 {4, 2, 5, 0, 3, 1},
 {5, 2, 1, 4, 3, 0},
 {1, 2, 0, 5, 3, 4},
 {0, 2, 4, 1, 3, 5},
 {0, 1, 2, 3, 4, 5},
 {4, 0, 2, 3, 5, 1},
 {5, 4, 2, 3, 1, 0},
 {1, 5, 2, 3, 0, 4},
 {5, 1, 3, 2, 4, 0},
 {1, 0, 3, 2, 5, 4},
 {0, 4, 3, 2, 1, 5},
 {4, 5, 3, 2, 0, 1},
 {1, 3, 5, 0, 2, 4},
 {0, 3, 1, 4, 2, 5},
 {4, 3, 0, 5, 2, 1},
 {5, 3, 4, 1, 2, 0},
 {3, 4, 5, 0, 1, 2},
 {3, 5, 1, 4, 0, 2},
 {3, 1, 0, 5, 4, 2},
 {3, 0, 4, 1, 5, 2},

 
 */

const int dice24[24][6] = {
    //
    {2, 1, 5, 0, 4, 3},
    {2, 0, 1, 4, 5, 3},
    {2, 4, 0, 5, 1, 3},
    {2, 5, 4, 1, 0, 3},
    {4, 2, 5, 0, 3, 1},
    {5, 2, 1, 4, 3, 0},
    {1, 2, 0, 5, 3, 4},
    {0, 2, 4, 1, 3, 5},
    {0, 1, 2, 3, 4, 5},
    {4, 0, 2, 3, 5, 1},
    {5, 4, 2, 3, 1, 0},
    {1, 5, 2, 3, 0, 4},
    {5, 1, 3, 2, 4, 0},
    {1, 0, 3, 2, 5, 4},
    {0, 4, 3, 2, 1, 5},
    {4, 5, 3, 2, 0, 1},
    {1, 3, 5, 0, 2, 4},
    {0, 3, 1, 4, 2, 5},
    {4, 3, 0, 5, 2, 1},
    {5, 3, 4, 1, 2, 0},
    {3, 4, 5, 0, 1, 2},
    {3, 5, 1, 4, 0, 2},
    {3, 1, 0, 5, 4, 2},
    {3, 0, 4, 1, 5, 2}
};

const int maxn = 4;
int colors[maxn][6];
int n;
int dice[maxn][6];
int posD[maxn];

int ans;

// posD[i] = val,  means No.i dice choose posture
// dice24[val][...]

void painting(int colors[][6], int dice[][6]) {
    // posD[i] = val, means No.i dice choose posture
    // dice24[val][..]
    
    for(int i = 0; i < n; i++) for(int j = 0; j < 6; j++) {
        // No.i dice surface j
        // dice[i][j] changed to position p = posD[i][j];
        // subscript is postion p
        // color[i][p] = dice[i][j]
        
        int p = dice24[posD[i]][j];
        colors[i][p] = dice[i][j];
    }
}


void solve() {
    // posD[i] = val, means No.i dice choose posture
    // dice24[val][..]
    
    painting(colors, dice);
    int tot = 0;
    for(int k = 0; k < 6; k++) {
        int cnt[maxn * 6];
        memset(cnt, 0, sizeof(cnt));
        
        int maxface = 0;
        for(int i = 0; i < n; i++) {
            maxface = max(maxface, ++cnt[colors[i][k]]);
            //debug(maxface);
        }
        
        tot += n-maxface;
    }
    
    ans = min(ans, tot);
    //debug(ans);
}

vector<string> nColor;
int getID(const char* name) {
    //
    string str(name);
    int id = (int)nColor.size();
    
    for(int i = 0; i < nColor.size(); i++) {
        if(nColor[i] == str) return i;
    }
    nColor.push_back(str);
    return id;
}



void dfs(int d) {
    if(d == n) solve();
    else {
        for(int i = 0; i < 24; i++) {
            // dice[24][..]
            // choose one posture of dice[24][..]
            // depth d cubes choose posture dice[i]
            
            posD[d] = i;
            //_for(i, 0, maxn) debug_(posD, i);
            dfs(d+1);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    while(scanf("%d", &n) == 1 && n) {
        //
        nColor.clear();
        //memset(posD, 0, sizeof(posD));
        //memset(colors, 0, sizeof(colors));
        
        for(int i = 0; i < n; i++) for(int j = 0; j < 6; j++) {
            char name[30];
            scanf("%s", name);
            dice[i][j] = getID(name);
            //debug(dice[i][j]);
        }
        
        // solve()
        //posD[0] = 0;
        
        ans = n*6;
        dfs(1);
        printf("%d\n", ans);
    }
}
