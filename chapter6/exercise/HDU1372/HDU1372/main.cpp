//
//  main.cpp
//  HDU1372
//
//  Created by zhangmin chen on 2019/3/3.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>

using namespace std;
#define debug(x) cout << #x << ": " << x << endl;
#define Set(x, v) memset(x, v, sizeof(x))

const int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int dy[] = {-1, -2, -2, -1, 1, 2, 2, 1};
// left , up, right, down

struct POS {
    int x, y;
    POS(int x, int y) : x(x), y(y) {}

};

bool operator== (const POS& a, const POS& b) {
    return a.x == b.x && a.y == b.y;
}

const int maxn = 16;
const int N = 8;


POS toPos(const char* str) {
    int xx = str[0] - 'a';
    int yy = str[1] - '1';
    return POS(xx, yy);
}

bool inRange(int x, int left, int right) {
    if(left > right) return inRange(x, right, left);
    return x >= left && x <= right;
}

int bfs(const POS& from, const POS& to) {
    int dis[N][N];
    memset(dis, -1, sizeof(dis));
    
    queue<POS> que;
    que.push(from);
    dis[from.x][from.y] = 0;
    
    while(!que.empty()) {
        const POS& f = que.front(); que.pop();
        int d = dis[f.x][f.y];
        if(f == to) return d;
        
        for(int i = 0; i < 8; i++) {
            int nx = f.x + dx[i];
            int ny = f.y + dy[i];
            if(dis[nx][ny] == -1 && inRange(nx, 0, N-1) && inRange(ny, 0, N-1)) {
                dis[nx][ny] = d+1;
                que.push(POS(nx, ny));
            }
        }
    }
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    char a[maxn], b[maxn];
    while(scanf("%s%s", a, b) == 2) {
        // to position
        POS s = toPos(a); POS t = toPos(b);
        int ans = bfs(s, t);
        printf("To get from %s to %s takes %d knight moves.\n", a, b, ans);
    }
}
