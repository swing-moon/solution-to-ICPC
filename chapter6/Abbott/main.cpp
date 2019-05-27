#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
    int r, c, d;
    Node(int r = 0, int c = 0, int d = 0) : r(r), c(c), d(d) {}
};

const int maxn = 10;
const char* dirs = "NESW";
const char* turns = "FLR";

int has_edge[maxn][maxn][4][3];
int d[maxn][maxn][4];
Node p[maxn][maxn][4];

int r0, c0, dir, r1, c1, r2, c2;

int dir_id(char c){
    return strchr(dirs, c) - dirs;
}

int turn_id(char c) {
    return strchr(turns, c) - turns;
}

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

Node walk(const Node& u, int turn) {
    int _dir = u.d;
    if(turn == 1)   _dir = (_dir + 3) % 4;
    if(turn == 2)   _dir = (_dir + 1) % 4;

    return Node(u.r+dr[_dir], u.c+dc[_dir], _dir);
}

bool inside(int r, int c) {
    return r >= 1 && r <= 9 && c >= 1 && c <= 9;
}

bool read_data() {
    char name[99], s[99];
    if(scanf("%s%d%d%s%d%d", name, &r0, &c0, s, &r2, &c2) != 6)
        return false;

    printf("%s\n",name);

    dir = dir_id(s[0]);
    r1 = r0 + dr[dir];
    c1 = c0 + dc[dir];

    memset(has_edge, 0, sizeof(has_edge));

    for(;;) {
        int r, c;
        scanf("%d",&r);
        if(r == 0) break;

        scanf("%d", &c);

        while(scanf("%s",s) == 1 && s[0] != '*') {
            for(int i = 1; i < strlen(s); i++) {
                has_edge[r][c][dir_id(s[0])][turn_id(s[i])] = 1;
            }
        }
    }
    return true;
}

void print_ans(Node u) {
    vector<Node> nodes;
    for(;;) {
        nodes.push_back(u);
        if(d[u.r][u.c][u.d] == 0) break;

        u = p[u.r][u.c][u.d];
    }

    nodes.push_back(Node(r0,c0,dir));

    int cnt = 0;
    for(int i = nodes.size()-1; i >= 0; i--) {
        if(cnt % 10 == 0)   printf(" ");
        printf(" (%d,%d)", nodes[i].r, nodes[i].c);
        if(++cnt % 10 == 0) printf("\n");
    }

    if(nodes.size() % 10 != 0)
        printf("\n");
}

void solve() {
    queue<Node> q;
    memset(d, -1, sizeof(d));
    Node root(r1, c1, dir);
    d[root.r][root.c][root.d] = 0;
    q.push(root);

    while(!q.empty()) {
        Node u = q.front(); q.pop();
        if(u.r == r2 && u.c == c2) {
            print_ans(u);
            return;
        }

        for(int i = 0; i < 3; i++) {
            Node v = walk(u, i);
            if(has_edge[u.r][u.c][u.d][i] && d[v.r][v.c][v.d] < 0 && inside(v.r, v.c)) {
                d[v.r][v.c][v.d] = d[u.r][u.c][u.d] + 1;
                p[v.r][v.c][v.d] = u;
                q.push(v);
            }
        }
    }
    printf("  No Solution Possible\n");
}

int main() {
    while(read_data()) {
        solve();
    }
}