//
//  main.cpp
//  LA5206-3
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

/** draw tree according to grid[][]  **/
struct Node {
    int color;
    Node* cld[4];
    Node() {
        Set(cld, NULL);
        color = -1;
    }
    void init() {
        Set(cld, NULL);
    }
};
typedef Node* Nodep;

Nodep build(POS& pos, int len) {
    Nodep nd =  new Node;

    int area = 0;
    _for(i, pos.x, pos.x+len) _for(j, pos.y, pos.y+len) area += grid[i][j];
    
    if(area == 0) {
        //
        nd->color = White;
        nd->init();
        return nd;
    }
    if(area == len*len) {
        //
        nd->color = Black;
        nd->init();
        return nd;
    }
    
    nd->color = Gray;
    int len2 = len/2;
    _for(i, 0, 4) {
        POS np(pos.x + dx[i]*len2, pos.y + dy[i]*len2);
        nd->cld[i] = build(np, len2);
    }
    return nd;
}
// tree = build()

void cal(Nodep root, vector<int>& path, vector<int>& ans) {
    if(root->color == White) return;
    if(root->color == Black) {
        int base = 1, sum = 0;
        _for(i, 0, path.size()) {
            sum += base * path[i];
            base *= 5;
        }
        ans.push_back(sum);
        return;
    }
    
    _for(d, 0, 4) {
        path.push_back(d+1);
        cal(root->cld[d], path, ans);
        path.pop_back();
    }
}



int main() {
    freopen("input.txt", "r", stdin);
    string line;
    for(int kase = 0; cin >> N && N; kase++) {
        //
        leafs.clear();
        if(kase) printf("\n");
        bool isGrid = N > 0; N = abs(N);
        
        if(isGrid) {
            // cin >> line
            _for(i, 0, N) {
                cin >> line;
                _for(j, 0, N) grid[i][j] = line[j] - '0';
            }
        } else {
            // cin >> leaf
            int val;
            while(cin >> val && val != -1) leafs.push_back(val);
            draw(leafs);
            // finished
        }
        
        printf("Image %d", kase+1);
        if(isGrid) {
            // build grid[][] tree
            POS st(0, 0);
            Nodep tree = build(st, N);
            vector<int> path, ans;
            cal(tree, path, ans);
            
            sort(ans.begin(), ans.end());
            _for(i, 0, ans.size()) {
                if(i % 12) printf(" "); else printf("\n");
                printf("%d", ans[i]);
            }
            printf("\n");
            printf("Total number of black nodes = %d\n", (int)ans.size());
            
        } else {
            //
            printf("\n");
            _for(i, 0, N) {
                _for(j, 0, N) printf("%c", grid[i][j] ? '*' : '.');
                printf("\n");
            }
        }
    }
}
