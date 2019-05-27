#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int maxs = 60 + 5;
// max square 25+16+9+4+1=55
const int maxm = 60 + 5;
// max matches = 2*5*6 = 60

// for matches : check if exists?
int n, exists[maxm];
// n : the length of edges

// for squares:
// contains[i][j] means square i contains match j
int contains[maxs][maxm];
int cnts, fullsqr[maxs], sqr[maxs];

int res;
// result

// row_m calculate the coordinate, not size
inline int row_m(int x, int y) {
    // intention: x start from 0
    // y start frome 0
    // id(matches) = id(showed) - 1, start from 0
    return (2*n+1) * x + y;
}

inline int row_c(int x, int y) {
    return (2*n+1) * x + y + n;
}

inline int tot_matches(int n) {
    return 2*n*(n+1);
}


void init() {
    int m, k;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < tot_matches(n); i++) exists[i] = 1;

    while(m--) {
        scanf("%d", &k);
        exists[k-1] = 0;
    }
}

void build() {
    cnts = 0;
    // cnts is cur square id

    memset(contains, 0, sizeof(contains));

    for(int sz = 1; sz <= n; sz++) {
        for(int x = 0; x < n; x++) {
            for(int y = 0; y < n; y++) {
                //
                sqr[cnts] = 0;
                fullsqr[cnts] = sz*4;

                for(int dl = 0; dl < sz; dl++) {
                    // max: x + dl
                    int a = row_m(x, y+dl);
                    //int b = row_m(x+dl, y+dl);
                    // I made a bug here, it's x+sz, not +dl
                    int b = row_m(x+sz, y+dl);
                    int c = row_c(x+dl, y);
                    int d = row_c(x+dl, y+sz);

                    contains[cnts][a] = 1;
                    contains[cnts][b] = 1;
                    contains[cnts][c] = 1;
                    contains[cnts][d] = 1;
                    // contains just a flag, mark if square i contains match j

                    sqr[cnts] += exists[a] + exists[b] + exists[c] + exists[d];
                }

                cnts++;
            }
        }
    }
}

int check_sqr() {
    for(int i = 0; i < cnts; i++) {
        if(sqr[i] == fullsqr[i]) return i;
    }
    return -1;
}

void dfs(int depth) {
    if(depth >= res ) return;

    int del = check_sqr();
    if(del == -1) {
        if(depth < res) res = depth;
        return;
    }

    // break checked square del --> del = id of broken square
    for(int edges = 0; edges < tot_matches(n); edges++) {
        if (contains[del][edges]) {
            // blue edges, cut
            exists[edges] = 0;
            // if the edge is deleted, the other squares will be broken
            for (int s = 0; s < cnts; s++)
                if (contains[s][edges]) sqr[s]--;
            dfs(depth + 1);
            for (int s = 0; s < cnts; s++)
                if (contains[s][edges]) sqr[s]++;
            exists[edges] = 1;
        }
    }
}


int main() {
    int T;
    scanf("%d", &T);

    while(T--) {
        init();
        build();
        res = n*n;
        dfs(0);
        printf("%d\n", res);
    }
    return 0;
}