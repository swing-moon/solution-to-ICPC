#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int maxn = 1000;
int n, m;
// n nodes, m edges

int u[maxn], v[maxn], w[maxn], rk[maxn], pa[maxn];
//int ans = 0;

bool cmp(const int i, const int j) {
    return w[i] < w[j];
}

int find(int x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}

int kruskal() {
    int ans = 0;
    for(int i = 0; i < n; i++) pa[i] = i;
    for(int i = 0; i < m; i++) rk[i] = i;
    sort(rk, rk+m, cmp);

    for(int i = 0; i < m; i++) {
        int eid = rk[i];
        int x = find(u[eid]), y = find(v[eid]);

        if(x != y) {
            ans += w[eid]; pa[x] = y;
        }
    }
    return ans;
}


int main() {
    cin >> n >> m;
    for(int i = 0; i < m; i++)
        cin >> u[i] >> v[i] >> w[i];

    cout << kruskal() << endl;
}