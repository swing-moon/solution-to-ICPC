//
//  main.cpp
//  LA5154
//
//  Created by zhangmin chen on 2019/4/18.
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

const int maxr = 20 + 5;
const int maxc = 10 + 5;

int R, C;
int vis[maxr][maxc], value[maxr][maxc];
char exp[maxr][maxc][128];

int read(const char* str, int& len) {
    //
    len = 0;
    int ans = 0, base = 1;
    while(str[len] && isdigit(str[len])) {
        //
        ans *= base;
        ans += str[len] - '0';
        base *= 10;
        
        len++;
    }
    return ans;
}

int canDfs(int r, int c) {
    // template of toposort()
    
    int& ok = vis[r][c];
    if(ok == -1) return false;
    else if(ok == 1) return true;
    
    ok = -1;
    // visit signed
    
    
    int& val = value[r][c];
    val = 0;
    
    const char* exp_ = exp[r][c];
    int len = (int)strlen(exp_), sign = 1;
    
    for(int i = 0; i < len; i++) {
        if(exp_[i] == '-') sign = -1;
        else if(exp_[i] == '+') sign = 1;
        else if(isdigit(exp_[i])) {
            // just digit, assign value
            int elen;
            int res = read(exp_+i, elen);
            
            val += res * sign;
            sign = 1;
            i += elen - 1;
            
        }
        else if(isupper(exp_[i])) {
            // A1+B2.... judge topo cycle?
            int elen;
            int row = exp_[i] - 'A';
            int col = read(exp_+i+1, elen);
            
            if(!canDfs(row, col)) return false;
            
            val += sign * value[row][col];
            
            sign = 1;
            i += elen - 1 + 1;
            // we add 'A', 'B', upper alpha
        }
    }
    
    // then is the true situation
    ok = 1;
    return true;
}


void dfs() {
    //
    memset(vis, 0, sizeof(vis));
    bool cycle = false;
    
    for(int i = 0; i < R; i++) for(int j = 0; j < C; j++) {
        bool ok = canDfs(i, j);
        
        if(!ok) {
            cycle = true;
            printf("%c%d: %s\n", 'A'+i, j, exp[i][j]);
        }
    }
    
    if(cycle) return;
    
    // then we can explain the exp
    printf(" ");
    for(int i = 0; i < C; i++) printf("%6d", i);
    cout << endl;
    
    for(int i = 0; i < R; i++) {
        printf("%c", i+'A');
        for(int j = 0; j < C; j++)
            printf("%6d", value[i][j]);
        cout << endl;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    while(true) {
        cin >> R >> C;
        if(R == 0 || C == 0) break;
        
        for(int i = 0; i < R; i++) for(int j = 0; j < C; j++) scanf("%s", exp[i][j]);
        
        // then we run solve()
        dfs();
        cout << endl;
    }
}
