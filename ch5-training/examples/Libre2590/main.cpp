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
#define Cpy(a, b) memcpy(a, b, sizeof(a))
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

const int maxn = 100000 + 10;
const int inf = 0x3f3f3f3f;
int N, M;
int A[maxn];

// == Graph definition ==
vector<int> G1[maxn];
vector<int> G2[maxn];
class Edge {
public:
    int to;
    Edge() {}
    Edge(int t) : to(t) {}
};
vector<Edge> edges1;
vector<Edge> edges2;

void initG1(int n) {
    _rep(i, 0, n) G1[i].clear();
    edges1.clear();
}

void initG2(int n) {
    _rep(i, 0, n) G2[i].clear();
    edges2.clear();
}

void addEdge1(int u, int v) {
    edges1.push_back(Edge(v));
    G1[u].push_back(edges1.size() - 1);
}

void addEdge2(int u, int v) {
    edges2.push_back(Edge(v));
    G2[u].push_back(edges2.size() - 1);
}
// == Graph definition finished ==

// == dijkstra, D[] used min, F[] used max ==
bool inq[maxn];
int D[maxn], F[maxn];

void initSpfa1() {
    Set(inq, 0);
    Set(D, inf);
    D[1] = A[1];
}

void initSpfa2() {
    Set(inq, 0);
    Set(F, -inf);
    F[N] = A[N];
}


void spfa1() {
    initSpfa1();
    queue<int> que1;
    que1.push(1);
    inq[1] = true;

    while (!que1.empty()) {
        int x = que1.front();
        que1.pop();
        inq[x] = false;

        _for(i, 0, G1[x].size()) {
            int y = edges1[G1[x][i]].to;
            if(D[x] < inf && D[y] > min(D[x], A[y])) {
                D[y] = min(D[x], A[y]);
                if(!inq[y]) {
                    que1.push(y);
                    inq[y] = true;
                }
            }
        }
    }
}

void spfa2() {
    initSpfa2();
    queue<int> que2;
    que2.push(N);
    inq[N] = 1;

    while (!que2.empty()) {
        int x = que2.front();
        que2.pop();
        inq[x] = false;

        _for(i, 0, G2[x].size()) {
            int y = edges2[G2[x][i]].to;
            if(F[x] > -inf && F[y] < max(F[x], A[y])) {
                F[y] = max(F[x], A[y]);
                if(!inq[y]) {
                    que2.push(y);
                    inq[y] = true;
                }
            }
        }
    }
}
// == dijkstra finished ==

int main() {
    freopen("input.txt", "r", stdin);
    cin >> N >> M;
    initG1(N);
    initG2(N);

    // get price data A[]
    _rep(i, 1, N) scanf("%d", &A[i]);

    // build Graph
    _rep(i, 1, M) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        addEdge1(x, y);
        addEdge2(y, x);

        if(z == 2) {
            addEdge1(y, x);
            addEdge2(x, y);
        }
    }

    // dijkstra
    spfa1();
    spfa2();

    int Ans = 0;
    _rep(i, 1, N) Ans = max(Ans, F[i] - D[i]);
    cout << Ans << endl;
}