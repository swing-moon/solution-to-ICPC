//
//  main.cpp
//  LA5206-2
//
//  Created by zhangmin chen on 2019/3/7.
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
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define _dfor(i, l, r) for(int i = (l); i >= r; i--)

const int dx[] = {0, 0, 1, 1};
const int dy[] = {0, 1, 0, 1};
// nw, ne, sw, se

const int maxn = 64 + 10;
typedef long long llong;
typedef vector<int>::iterator VII;
typedef map<int, int>::iterator MII;
enum color{ White = 0, Black = 1, Gray = 2 };
//char img[maxn][maxn];
int grid[maxn][maxn];

int N;

struct POS {
    int x, y;
    POS(int x, int y) : x(x), y(y) {}
};

/** draw tree **/
vector<int> leafs;
// locate blocks and draw

void locate(int leaf, int& len, POS& pos) {
    len = N;
    pos.x = 0; pos.y = 0;
    
    while(leaf) {
        int dir = leaf % 5 - 1;
        len /= 2;
        
        //locate:
        pos.x += dx[dir]*len; pos.y += dy[dir]*len;
        leaf /= 5;
    }
}
void draw(vector<int>& leafs) {
    //Set(img, '.');
    Set(grid, 0);
    for(int i = 0; i < leafs.size(); i++) {
        int cur = leafs[i];
        int len;
        POS pos(0, 0);
        
        locate(cur, len, pos);
        
        _for(r, 0, len) _for(c, 0, len) grid[pos.x+r][pos.y+c] = 1;
        
    }
}

// build q-tree
//bool vis[maxn][maxn];

void build(POS pos, int len, int val, int base, vector<int>& ans) {
    //
    int area = 0, len2 = len/2;
    _for(i, pos.x, pos.x+len) _for(j, pos.y, pos.y+len) area += grid[i][j];
    
    if(area == 0) return;
    if(area == len*len) {
        ans.push_back(val);
        return;
    }
    
    _for(d, 0, 4) {
        POS np(pos.x + dx[d]*len2, pos.y + dy[d]*len2);
        
        int nval = val + base*(d+1);
        int nbase = base*5;
        build(np, len2, nval, nbase, ans);
    }
}



int main() {
    freopen("input.txt", "r", stdin);
    string line;
    
    for(int kase = 0; cin >> N && N; kase++) {
        leafs.clear();
        //res.clear();
        //Set(vis, 0);
        
        if(kase) printf("\n");
        bool isGrid = N > 0; N = abs(N);
        
        if(isGrid) {
            _for(i, 0, N) {
                cin >> line;
                _for(j, 0, N) grid[i][j] = line[j] - '0';
            }
        } else {
            //
            int val;
            while(cin >> val && val != -1) leafs.push_back(val);
            draw(leafs);
            // finished!
        }
        
        printf("Image %d", kase+1);
        
        if(isGrid) {
            POS st(0, 0);
            //
            // val = 0, base = 1
            vector<int> res;
            build(st, N, 0, 1, res);
            
            sort(res.begin(), res.end());
            _for(i, 0, res.size()) {
                if(i % 12) printf(" "); else printf("\n");
                printf("%d", res[i]);
            }
            printf("\n");
            printf("Total number of black nodes = %d\n", res.size());
            
        } else {
            printf("\n");
            _for(i, 0, N) {
                _for(j, 0, N) printf("%c", grid[i][j] ? '*' : '.');
                printf("\n");
            }
        }
    }
}
