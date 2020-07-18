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
#include <bitset>
#include <assert.h>

using namespace std;
typedef long long ll;
typedef set<int>::iterator ssii;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _forS(i, l, r) for(set<int>::iterator i = (l); i != (r); i++)
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define _forDown(i, l, r) for(int i = (l); i >= r; i--)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;
#define debugArr(arr, x, y) _for(i, 0, x) { _for(j, 0, y) printf("%c", arr[i][j]); printf("\n"); }
#define _forPlus(i, l, d, r) for(int i = (l); i + d < (r); i++)
#define lowbit(i) (i & (-i))
#define MPR(a, b) make_pair(a, b)

const int maxN = 4000 + 10;
const int inf = 0x3f3f3f3f;
int nCities = 0;
const int maxn = 100;
vector<int> tickets[maxn];
int cost[maxn];
int NT, NI;

// == Graph ==
vector<int> G[maxN];

class Edge {
public:
    int from, to, weight, val;
    Edge() {}
    Edge(int u, int v, int w, int val) : from(u), to(v), weight(w), val(val) {}
};

class Node {
public:
    int u, dist;
    Node() {}
    Node(int u, int dist) : u(u), dist(dist) {}
    bool operator< (const Node& rhs) const {
        return dist > rhs.dist;
    }
};

vector<Edge> edges;

void initG() {
    _for(i, 0, maxN) G[i].clear();
    edges.clear();
}

void addEdge(int u, int v, int w, int val) {
    edges.push_back(Edge(u, v, w, val));
    G[u].push_back(edges.size() - 1);
}
// == Graph finsihed ==

// == dijkstra ==
int D[maxN], vis[maxN];
int pid[maxN];

void initDij(int st) {
    _for(i, 0, maxN) D[i] = inf;
    D[st] = 0;

    Set(vis, 0);
    Set(pid, 0);
}

void dijsktra(int st) {
    initDij(st);
    priority_queue<Node> que;
    que.push(Node(st, 0));

    while (!que.empty()) {
        int x = que.top().u;
        que.pop();
        if(vis[x]) continue;
        vis[x] = 1;

        _for(i, 0, G[x].size()) {
            const Edge& e = edges[G[x][i]];
            int y = e.to;
            if(D[y] > D[x] + e.weight) {
                D[y] = D[x] + e.weight;
                pid[y] = G[x][i];
                que.push(Node(y, D[y]));
            }
        }
    }
}

vector<int> getPath(int ed, const int st) {
    vector<int> path;
    while (ed != st) {
        path.push_back(edges[pid[ed]].val);
        ed = edges[pid[ed]].from;
    }
    reverse(path.begin(), path.end());
    return path;
}
// == dijkstra finsihed ==

// == get all tickets ==
map<int, int> cityID;

inline int ID(int x) {
    if(cityID.count(x)) return cityID[x];
    cityID[x] = ++nCities;
    return nCities;
}

inline int ID(int i, int j) {
    return (i - 1) * nCities + j;
}

void getTickets(const int NT) {
    _for(i, 0, NT) {
        tickets[i].clear();
        int len;
        scanf("%d%d", &cost[i], &len);
        while (len--) {
            int x;
            scanf("%d", &x);
            tickets[i].push_back(ID(x));
        }
    }
}
// == get tickets finished ==

// == get trip data ==
vector<int> toList;
int getTrip(const int trip) {
    toList.clear();
    int tot = 0;
    scanf("%d", &tot);

    _for(i, 0, tot) {
        int x;
        scanf("%d", &x);
        toList.push_back(ID(x));
    }

    return tot;
}
// == trip finished ==

// == chooseTicket for trip ==
void chooseTicket(const vector<int>& toList, const int tot) {
    _for(i, 0, NT) _rep(k, 1, tot) {
        int cur = tickets[i][0];
        int k2 = k;

        _for(j, 1, tickets[i].size()) {
            int A = tickets[i][j];
            if(A == toList[k2]) k2++;
            if(k2 > tot) break;

            addEdge(ID(k, cur), ID(k2, A), cost[i], i + 1);
            if(k2 == tot) break;
        }
    }
}
// == chooseTicket finished ==

void init() {
    nCities = 0;
    cityID.clear();
    _for(i, 0, maxn) tickets[i].clear();
    Set(cost, 0);
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;
    while (scanf("%d", &NT) == 1 && NT) {
        init();

        // get tickets
        getTickets(NT);
        scanf("%d", &NI);
        kase++;

        _rep(trip, 1, NI) {
            int tot = getTrip(trip);
            assert(toList.size() != 0);

            initG();
            chooseTicket(toList, tot);
            int src = ID(1, toList[0]), ed = ID(tot, toList[tot-1]);
            dijsktra(src);

            printf("Case %d, Trip %d: Cost = %d\n", kase, trip, D[ed]);
            printf("  Tickets used:");

            vector<int> res = getPath(ed, src);
            _for(i, 0, res.size()) printf(" %d", res[i]);
            printf("\n");
        }
    }
}
