#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <queue>


using namespace std;

struct Node {
    int bug, dist;
//    Node(int bug, int dist) : bug(bug), dist(dist) {}

    bool operator < (const Node& rhs) const {
        return dist > rhs.dist;
    }
};

int n, m;
const int maxn = 20 + 5;
const int maxm = 100 + 5;
const int inf = 0x3f3f3f3f;

int d[1<<maxn];
int vis[1<<maxn];
int t[maxm];
char before[maxm][maxn], after[maxm][maxn];

int dijkstra() {
    for(int i = 0; i < (1<<n); i++) {
        // bug = i
        d[i] = inf; vis[i] = 0;
    }

    // remember judge vis[] and [d];

    priority_queue<Node> q;
    Node start; start.bug = (1<<n) - 1; start.dist = 0;
    q.push(start);
    d[start.bug] = 0;

    while(!q.empty()) {
        Node u = q.top(); q.pop();
        if(u.bug == 0) return d[u.bug];
        // judge vis[]
        if(vis[u.bug]) continue;
        vis[u.bug] = 1;

        // dijkstra, travel all the edges
        // start from u
        for(int i = 0; i < m; i++) {
            // patchable? if not, continue; if yes, judge the next node
            bool patchable = true;
            for(int j = 0; j < n; j++) {
                // travel all the bugs
                int mask = (1<<j);
                if(before[i][j] == '-' && (mask & u.bug)) { patchable = false; break; }
                if(before[i][j] == '+' && !(mask & u.bug)) { patchable = false; break; }
            }
            if(!patchable) continue;

            Node u2;
            // try to patch u2
            u2.bug = u.bug;
            for(int k = 0; k < n; k++) {
                // after[i][k]
                // 1->0, &= ~();  0->1 |= ()
                int mask = (1<<k);
                if(after[i][k] == '-') u2.bug &= (~mask);
                if(after[i][k] == '+') u2.bug |= mask;
            }

            // try to find shortest dist, dp
            // u2.dist = u.dist + t[i]
            int& D = d[u2.bug];

            if(D < 0 || D > u.dist + t[i]) {
                D = u.dist + t[i];
                q.push( (Node){u2.bug, D} );
            }
        }
    }
    return -1;
}

int main() {
    int kase = 0;
    while(scanf("%d%d", &n, &m) == 2 && n) {
        //
        for(int i = 0; i < m; i++) scanf("%d%s%s",&t[i], before[i], after[i]);
        int ans = dijkstra();
        //cout << ans << endl;

        printf("Product %d\n", ++kase);
        if(ans < 0) printf("Bugs cannot be fixed.\n\n");
        else printf("Fastest sequence takes %d seconds.\n\n", ans);
    }
}