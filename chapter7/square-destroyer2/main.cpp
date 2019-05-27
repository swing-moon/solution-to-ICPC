#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long llong;

const int maxs = 60 + 5;
const int maxm = 60 + 5;
const int maxsz = 5 + 1;

llong cell[maxsz][maxsz];
// it means a cell[i][j] , it's a square
//llong State;

llong sqr[maxs];
llong bit[maxm];
// bit[0] = 0001
// bit[1] = 0010
// bit[2] = 0100
// bit[3] = 1000


int n, maxd, cnts;
int tot_matches;

inline int row_mid(int x, int y) {
    // intention; x start from 0, y start from 0
    // id(matches) = id(showed)-1
    return (2*n+1) * x + y;
}

inline int col_mid(int x, int y) {
    return (2*n+1) * x + y + n;
}

// we need get tot_matches


void build() {
    memset(cell, 0, sizeof(cell));
    memset(sqr, 0, sizeof(sqr));
    cnts = 0;
    // sqr[] from 0 to cnts-1
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
//            cell[i][j] = 0;
            cell[i][j] |= (bit[row_mid(i,j)] | bit[row_mid(i+1,j)]);
            cell[i][j] |= (bit[col_mid(i,j)] | bit[col_mid(i,j+1)]);
            sqr[cnts] = cell[i][j];
            cnts++;
        }

    // stretching  size > 1
    for(int sz = 2; sz <= n; sz++) {
        // x, y is the start coordinate
        for(int x = 0; x+sz-1 < n; x++)
            for(int y = 0; y+sz-1 < n; y++) {
//                sqr[cnts] = 0;
                for(int w = 0; w < sz; w++) {
                    for(int h = 0; h < sz; h++) {
                        sqr[cnts] ^= cell[x+w][y+h];
                        // only eliminate matches
                    }
                }

                cnts++;
                // I made a bug here
            }
    }
//    cout << "tot squares is " << cnts << endl;
}

bool dfs(int depth, llong State) {
    if(depth == maxd) {
        for(int i = 0; i < cnts; i++)
            if((sqr[i] & State) == sqr[i]) return false;
        return true;
    }

    llong si = State;
    int h = 0, del = 0;
    // del is the binary value of the block which will be broken

    for(int i = 0; i < cnts; i++) {
        if((sqr[i] & si) == sqr[i]) {
            h++;
            si ^= sqr[i];
            if(!del) del = sqr[i];
        }
    }
    if(h + depth > maxd) return false;
    // h is the max moves to break all the cell

    for(int i = 0; i < tot_matches; i++) {
        // all matches, matches id start from 0 --> (0...tot_matches-1)
        if((bit[i] & del) == bit[i])
            // check the match should be moved!
            if(dfs(depth+1, State^bit[i])) return true;
            // i made a bug here!
    }
    return false;
}




int main() {
    int T;
    scanf("%d", &T);
    bit[0] = 1;
    for(int i = 1; i <= 60; i++) bit[i] = bit[i-1] << 1;
    llong State;

    // bit[0] = 0001
    // bit[1] = 0010
    // bit[2] = 0100
    // matches id from 0 to tot_matches-1 (0, 1, .... tot_matches-1)
    // if tot_matches = 3
    // state = 111 = bit[3]-1

    int m, k;

    while(T--) {
        scanf("%d%d", &n, &m);
        tot_matches = 2*n*(n+1);
        State = bit[tot_matches] - 1;

        for(int loop = 0; loop < m; loop++) {
            scanf("%d", &k);
            State ^= bit[k-1];
        }

        build();

        for(maxd = 0; ;maxd++) {
            if(dfs(0, State)) break;
        }
        printf("%d\n", maxd);
    }
}