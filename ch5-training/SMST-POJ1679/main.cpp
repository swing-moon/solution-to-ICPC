#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <map>

using namespace std;
const int maxn = 100 + 10;
const int inf = 0x3f3f3f3f;
int passMax[maxn][maxn];

int n, m;

struct Edge {
    int from, to, dist, inTree;
    bool operator < (const Edge& rhs) const {
        return dist < rhs.dist;
    }
};

struct Tree {
    int to, dist;
};

struct Node {
    //
    int id, maxD;
};

vector<int> G[maxn];
vector<Tree> tree[maxn];
vector<Edge> edges;

int pa[maxn];


void init() {
    edges.clear();
    for(int i = 0; i < maxn; i++) G[i].clear();
    for(int i = 0; i < maxn; i++) pa[i] = i;
    memset(passMax, 0, sizeof(passMax));
}

void addEdge(int from, int to, int dist, int inTree) {
    //
    edges.push_back((Edge){from, to, dist, inTree});
    int cnt_m = edges.size();
    G[from].push_back(cnt_m - 1);
}

void addTree(const Edge& e) {
    tree[e.from].push_back((Tree){e.to, e.dist});
    tree[e.to].push_back((Tree){e.from, e.dist});
}

int findset(int x) {
    return x == pa[x] ? x : pa[x] = findset(pa[x]);
}


int kruskal() {
    //
    sort(edges.begin(), edges.end());
    int mst = 0, cnt = 0;
    for(int i = 0; i < edges.size(); i++) {
        Edge& e = edges[i];
        int u = findset(e.from), v = findset(e.to);

        if(u != v) {
            pa[u] = v;
            addTree(e);
            e.inTree = 1;

            mst += e.dist;
            if(++cnt == n-1) break;
        }
    }
    return mst;
}


void bfs(int u) {
    bool vis[maxn];
    memset(vis, 0, sizeof(vis));

    queue<Node> que;
    que.push((Node){u, 0});

    vis[u] = 1;
    while(!que.empty()) {
        Node cur = que.front(); que.pop();

        for(int i = 0; i < tree[cur.id].size(); i++) {
            //
            Tree& E = tree[cur.id][i];
            int maxE = E.dist;

            if(!vis[E.to]) {
                // I made a bug here! e.inTree
                // find passMax in MST

                if(cur.maxD > maxE) maxE = cur.maxD;
                // maxE = max(maxE, cur.maxD);
                // cout << "maxE: " << maxE << endl;

                passMax[u][E.to] = maxE;
                // (cur, e.to) dp, find maxE
                vis[E.to] = 1;
                que.push((Node){E.to, maxE});
            }
        }
    }
}

void printEdge(const Edge& e) {
    printf("%d %d %d", e.from, e.to, e.dist);
    printf("   pass:  %d\n", passMax[e.from][e.to]);

}

void second_MST() {
    int mst = kruskal();

    for(int i = 0; i < n; i++)
        bfs(i);

    int smst = inf;
    for(int i = 0; i < edges.size(); i++) {
        Edge& e = edges[i];
        if(!e.inTree) {
            if(mst + e.dist - passMax[e.from][e.to] < smst)
                smst = mst + e.dist - passMax[e.from][e.to];
        }
    }


    if(smst == mst) {
        printf("Not Unique!\n");
    }
    else {
        printf("%d\n", mst);
    }
}



int T;
int main() {
    scanf("%d", &T);

    while(T--) {
        init();

        // int n, m;
        scanf("%d%d", &n, &m);

        for(int i = 0; i < m; i++) {
            // addEdge()
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w); u--; v--;
            addEdge(u, v, w, 0);
        }

        // kruskal()
        // cout << kruskal() << endl;

        second_MST();
    }
}