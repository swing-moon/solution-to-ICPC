//
//  main.cpp
//  LA5164
//
//  Created by zhangmin chen on 2019/7/9.
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

const int maxn = 20 + 5;
const int maxk = 50 + 5;
const int MAX = 256;
int N, K;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _forS(i, l, r) for(set<int>::iterator i = (l); i != (r); i++)
#define _forV(i, l, r) for(vector<Pos>::iterator i = (l); i != (r); i++)
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define _forDown(i, l, r) for(int i = (l); i >= r; i--)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;
#define debugArr(arr, x, y) _for(i, 0, x) { _for(j, 0, y) printf("%c", arr[i][j]); printf("\n"); }
#define _forPlus(i, l, d, r) for(int i = (l); i + d < (r); i++)


class Pos {
public:
    int x, y;
    Pos(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
const char DIR[] = {'w', 's', 'e', 'n'};
// (dx[dir], dy[dir]) => DIR[dir]

vector<Pos> blocks;
int vis[MAX * 2][MAX * 2];

bool inRange(int x, int left, int right) {
    if(left > right) return inRange(x, right, left);
    return left <= x && x <= right;
}

bool isBlock(const Pos& src, const Pos& dest) {
    if(src.x == dest.x) {
        for(auto b : blocks) {
            if(src.x == b.x && inRange(b.y, src.y, dest.y)) return true;
        }
    }
    else if(src.y == dest.y) {
        for(auto b : blocks) {
            if(src.y == b.y && inRange(b.x, src.x, dest.x)) return true;
        }
    }
    return false;
}


void init() {
    blocks.clear();
    Set(vis, 0);
}

ostream& operator<< (ostream& os, const vector<char>& path) {
    for(const auto p : path) os << p;
    return os;
}

bool h(const Pos& pos, const vector<char>& path) {
    int dist = abs(pos.x) + abs(pos.y);
    int d = (int)path.size();
    int walk = (N + d + 1) * (N - d) / 2;
    
    return walk < dist;
}
// usage: if(h(pos, path)) dfs return

void dfs(const Pos& pos, vector<char>& path, vector<string>& paths) {
    if(path.size() == N) {
        if(pos.x == 0 && pos.y == 0) {
            stringstream ss;
            ss << path;
            paths.push_back(ss.str());
        }
        return;
    }
    
    if(h(pos, path)) return;
    
    _for(dir, 0, 4) {
        // find invalid move
        const char D = DIR[dir];
        int len = (int)path.size() + 1;
        if(path.size()) {
            const char last = path.back();
            
            if(last == D) continue;
            if(last == 'w' && D == 'e') continue;
            if(last == 'n' && D == 's') continue;
            if(last == 'e' && D == 'w') continue;
            if(last == 's' && D == 'n') continue;
        }
        
        Pos nxt(pos.x + dx[dir] * len, pos.y + dy[dir] * len);
        if(isBlock(pos, nxt)) continue;
        
        if(vis[nxt.x + MAX][nxt.y + MAX]) continue;
        
        vis[nxt.x + MAX][nxt.y + MAX] = 1;
        path.push_back(D);
        dfs(nxt, path, paths);
        path.pop_back();
        vis[nxt.x + MAX][nxt.y + MAX] = 0;
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);
    
    while (kase--) {
        init();
        scanf("%d%d", &N, &K);
        Pos b;
        _for(i, 0, K) {
            scanf("%d%d", &b.x, &b.y);
            blocks.push_back(b);
        }
        
        // finish input
        // solve the problem
        Pos src(0, 0);
        vector<char> path;
        vector<string> paths;
        
        dfs(src, path, paths);
        
        sort(paths.begin(), paths.end());
        _for(i, 0, paths.size()) cout << paths[i] << endl;
        printf("Found %lu golygon(s).\n\n", paths.size());
    }
}
