#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;
const int maxn = 500 + 10;

int W, H, N;
int X1[maxn], X2[maxn], Y1[maxn], Y2[maxn];

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

bool fld[maxn*6][maxn*6];

int read() {
    int x; scanf("%d", &x); return x;
}

int compress(int* x1, int* x2, int w) {
    vector<int> vec;

    for(int i = 0; i < N; i++) {
        for(int d = -1; d <= 1; d++) {
            int tx1 = x1[i] + d, tx2 = x2[i] + d;
            if(1 <= tx1 && tx1 <= w) vec.push_back(tx1);
            if(1 <= tx2 && tx2 <= w) vec.push_back(tx2);
        }
    }

    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());

    for(int i = 0; i < N; i++) {
        x1[i] = find(vec.begin(), vec.end(), x1[i]) - vec.begin();
        x2[i] = find(vec.begin(), vec.end(), x2[i]) - vec.begin();
    }
    /*
    for(int i = 0; i < N; i++) printf("%d ", x1[i]); puts("");
    for(int i = 0; i < N; i++) printf("%d ", x2[i]); puts("");
    */


    return vec.size();
}

int main() {
    W = read(), H = read(), N = read();
    for(int i = 0; i < N; i++) X1[i] = read();
    for(int i = 0; i < N; i++) X2[i] = read();
    for(int i = 0; i < N; i++) Y1[i] = read();
    for(int i = 0; i < N; i++) Y2[i] = read();

    W = compress(X1, X2, W);
    H = compress(Y1, Y2, H);

    memset(fld, 0, sizeof(fld));

    for(int i = 0; i < N; i++) {
        for(int y = Y1[i]; y <= Y2[i]; y++) {
            for(int x = X1[i]; x <= X2[i]; x++) {
                fld[y][x] = true;
            }
        }
    }

    int ans = 0;
    for(int y = 0; y < H; y++) {
        for(int x = 0; x < W; x++) {
            if(fld[y][x]) continue;
            ans++;

            queue<pair<int, int> > que;
            // bfs white grid to the furthest!

            que.push(make_pair(x, y));
            while(!que.empty()) {
                int sx = que.front().first, sy = que.front().second; que.pop();

                for(int dir = 0; dir < 4; dir++) {
                    int tx = sx + dx[dir], ty = sy + dy[dir];
                    if(tx < 0 || tx >= W || ty < 0 || ty >= H) continue;

                    if(fld[ty][tx]) continue;
                    que.push(make_pair(tx, ty));
                    fld[ty][tx] = true;
                }
            }
        }
    }
    printf("%d\n", ans);
}